#include "CukeToggleSwitch.h"
#include "CukeToggleSwitchPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, QColor, KnobColor)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, qreal, KnobDiameter)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, qreal, KnobCenterY)

CukeToggleSwitch::CukeToggleSwitch(QWidget *parent)
    : QWidget(parent),
      CukeScope(this),
      _pKnobCenterX(-1),
      d_ptr(new CukeToggleSwitchPrivate(this)) {
    Q_D(CukeToggleSwitch);
    setFixedSize(44, 22);
    _pKnobColor = cTheme->getThemeColor(getThemeMode(), CukeThemeType::ToggleSwitchKnob);
    _pBgColor = cTheme->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha);

    // 属性名与 Q_PROPERTY 中的一致
    d->_bgAnimation = new QPropertyAnimation(this, "_pBgColor", this);
    d->_bgAnimation->setDuration(200);
    d->_bgAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d->_knobColorAnimation = new QPropertyAnimation(this, "_pKnobColor", this);
    d->_knobColorAnimation->setDuration(200);
    d->_knobColorAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d->_knobDiameterAnimation = new QPropertyAnimation(this, "_pKnobDiameter", this);
    d->_knobDiameterAnimation->setDuration(200);
    d->_knobDiameterAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d->_moveAnimation = new QPropertyAnimation(this, "_pKnobCenterX", this);
    d->_moveAnimation->setDuration(200);
    d->_moveAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_bgAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_knobColorAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_knobDiameterAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_moveAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));

    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeToggleSwitch::onThemeChanged);
}

CukeToggleSwitch::~CukeToggleSwitch() = default;

void CukeToggleSwitch::onThemeChanged(CukeThemeType::ThemeMode Mode) {
    Q_D(CukeToggleSwitch);
    CukeScope::onThemeChanged(Mode);

    _pKnobColor = (getThemeMode() == CukeThemeType::Light) ^ d->_isToggled
                      ? cTheme->getThemeColor(CukeThemeType::Light, CukeThemeType::ToggleSwitchKnob)
                      : cTheme->getThemeColor(CukeThemeType::Dark, CukeThemeType::ToggleSwitchKnob);
    update();
}

void CukeToggleSwitch::setIsToggled(bool isToggled) {
    Q_D(CukeToggleSwitch);
    if (d->_isToggled == isToggled) return;
    d->_isToggled = isToggled;
    // 立即跳到对应位置
    _pKnobCenterX = d->_isToggled ? d->knobCenterXR : d->knobCenterXL;
    update();
}

bool CukeToggleSwitch::getIsToggled() {
    Q_D(CukeToggleSwitch);
    return d->_isToggled;
}

void CukeToggleSwitch::setKnobCenterX(qreal knobX) {
    if (!qFuzzyCompare(_pKnobCenterX + 1.0, knobX + 1.0)) {
        // qFuzzyCompare 对 qreal 比较
        _pKnobCenterX = knobX;
        update();
    }
}

qreal CukeToggleSwitch::getKnobCenterX() const {
    return _pKnobCenterX;
}

void CukeToggleSwitch::mousePressEvent(QMouseEvent *event) {
    Q_D(CukeToggleSwitch);
    d->_isPressed = true;
    QPointF mousePos = event->pos();
    qreal radius = _pKnobDiameter * 0.5;
    QRectF knobRect(_pKnobCenterX - radius, _pKnobCenterY - radius,
                    _pKnobDiameter, _pKnobDiameter);

    if (knobRect.contains(mousePos)) {
        // 动画到 Press 状态直径
        d->_knobDiameterAnimation->stop();
        d->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
        d->_knobDiameterAnimation->setEndValue(d->knobDiameterPress);
        d->_knobDiameterAnimation->start();
    }

    update();
    QWidget::mousePressEvent(event);
}

void CukeToggleSwitch::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(CukeToggleSwitch);
    d->_isPressed = false;

    // 松开
    QPointF mousePos = event->pos();
    qreal radius = _pKnobDiameter * 0.5;
    QRectF knobRect(_pKnobCenterX - radius, _pKnobCenterY - radius,
                    _pKnobDiameter, _pKnobDiameter);
    d->_knobDiameterAnimation->stop();
    d->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
    if (knobRect.contains(mousePos)) {
        d->_knobDiameterAnimation->setEndValue(d->knobDiameterHover);
    } else {
        d->_knobDiameterAnimation->setEndValue(d->knobDiameter);
    }
    d->_knobDiameterAnimation->start();

    // 切换状态
    d->_isToggled = !d->_isToggled;
    emit toggled(d->_isToggled);

    d->_bgAnimation->stop();
    d->_bgAnimation->setStartValue(_pBgColor);
    d->_bgAnimation->setEndValue(d->_isToggled
                                         ? cTheme->getThemeColor(getThemeMode(), CukeThemeType::CheckAlpha)
                                         : cTheme->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha));
    d->_bgAnimation->start();

    d->_knobColorAnimation->stop();
    d->_knobColorAnimation->setStartValue(_pKnobColor);
    d->_knobColorAnimation->setEndValue((getThemeMode() == CukeThemeType::Light) ^ d->_isToggled
                                                ? cTheme->getThemeColor(CukeThemeType::Light, CukeThemeType::ToggleSwitchKnob)
                                                : cTheme->getThemeColor(CukeThemeType::Dark, CukeThemeType::ToggleSwitchKnob));
    d->_knobColorAnimation->start();

    // 使用当前 knobX 作为起点，目标为左右位置
    d->_moveAnimation->stop();
    d->_moveAnimation->setStartValue(_pKnobCenterX);
    d->_moveAnimation->setEndValue(d->_isToggled ? d->knobCenterXR : d->knobCenterXL);
    d->_moveAnimation->start();

    QWidget::mouseReleaseEvent(event);
}

void CukeToggleSwitch::enterEvent(QEnterEvent *event) {
    setMouseTracking(true);
    QWidget::enterEvent(event);
}

void CukeToggleSwitch::leaveEvent(QEvent *event) {
    setMouseTracking(false);
    QWidget::leaveEvent(event);
}

void CukeToggleSwitch::mouseMoveEvent(QMouseEvent *event) {
    Q_D(CukeToggleSwitch);
    QPointF mousePos = event->pos();

    qreal radius = _pKnobDiameter * 0.5;
    QRectF knobRect(_pKnobCenterX - radius, _pKnobCenterY - radius,
                    _pKnobDiameter, _pKnobDiameter);

    if (knobRect.contains(mousePos)) {
        if (!qFuzzyCompare(_pKnobDiameter + 1.0, d->knobDiameterHover + 1.0)) {
            d->_knobDiameterAnimation->stop();
            d->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
            d->_knobDiameterAnimation->setEndValue(d->knobDiameterHover);
            d->_knobDiameterAnimation->start();
        }
    } else {
        if (!qFuzzyCompare(_pKnobDiameter + 1.0, d->knobDiameter + 1.0)) {
            d->_knobDiameterAnimation->stop();
            d->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
            d->_knobDiameterAnimation->setEndValue(d->knobDiameter);
            d->_knobDiameterAnimation->start();
        }
    }
    QWidget::mouseMoveEvent(event);
}


void CukeToggleSwitch::resizeEvent(QResizeEvent *event) {
    Q_D(CukeToggleSwitch);
    QWidget::resizeEvent(event);

    const qreal margin = 4.0;
    const qreal penW = 2.0;
    QRectF contentRect = QRectF(rect()).adjusted(1.0 + penW / 2.0,
                                                 1.0 + penW / 2.0,
                                                 -1.0 - penW / 2.0,
                                                 -1.0 - penW / 2.0);
    const qreal h = contentRect.height();

    // knob 的基本直径
    d->knobDiameter = qMax<qreal>(0.0, h - 2.0 * margin);
    d->knobDiameterHover = d->knobDiameter * 1.2;
    d->knobDiameterPress = d->knobDiameter * 0.8;

    // 圆心 Y 用 contentRect 的中心
    _pKnobCenterY = contentRect.top() + h * 0.5;

    // 左右圆心 X
    d->knobCenterXL = contentRect.left() + margin + d->knobDiameter * 0.5;
    d->knobCenterXR = contentRect.right() - margin - d->knobDiameter * 0.5;

    _pKnobDiameter = d->knobDiameter;

    if (_pKnobCenterX < 0.0) {
        _pKnobCenterX = d->_isToggled ? d->knobCenterXR : d->knobCenterXL;
    }
}


void CukeToggleSwitch::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const qreal penW = 2.0; // 与 resizeEvent 保持一致
    QRectF contentRect = QRectF(rect()).adjusted(1.0 + penW / 2.0,
                                                 1.0 + penW / 2.0,
                                                 -1.0 - penW / 2.0,
                                                 -1.0 - penW / 2.0);
    const qreal h = contentRect.height();

    // 背景
    p.setPen(Qt::NoPen);
    p.setBrush(_pBgColor);
    p.drawRoundedRect(contentRect, h / 2.0, h / 2.0);

    // 边框
    p.setPen(QPen(cTheme->getThemeColor(getThemeMode(), CukeThemeType::ToggleSwitchBorder), penW));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(contentRect, h / 2.0, h / 2.0);

    // 圆钮
    qreal radius = _pKnobDiameter * 0.5;
    p.setPen(Qt::NoPen);
    p.setBrush(isEnabled() ? _pKnobColor : cTheme->getThemeColor(getThemeMode(), CukeThemeType::TextDisable));
    p.drawEllipse(QPointF(_pKnobCenterX, _pKnobCenterY), radius, radius);
}

CUKE_NAMESPACE_END(pub)