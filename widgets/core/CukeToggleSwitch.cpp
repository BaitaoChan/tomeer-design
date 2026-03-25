#include "CukeToggleSwitch.h"
#include "CukeToggleSwitchPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, QColor, KnobColor)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, qreal, KnobDiameter)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, qreal, KnobCenterY)

CukeToggleSwitch::CukeToggleSwitch(QWidget *parent)
    : QWidget(parent),
      CukeHub(this),
      _pKnobCenterX(-1),
      d_ptr(new CukeToggleSwitchPrivate(this)) {
    setFixedSize(44, 22);
    _pKnobColor = cTheme->getThemeColor(getThemeMode(), CukeThemeType::ToggleSwitchKnob);
    _pBgColor = cTheme->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha);

    // 属性名与 Q_PROPERTY 中的一致
    d_ptr->_bgAnimation = new QPropertyAnimation(this, "_pBgColor", this);
    d_ptr->_bgAnimation->setDuration(200);
    d_ptr->_bgAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d_ptr->_knobColorAnimation = new QPropertyAnimation(this, "_pKnobColor", this);
    d_ptr->_knobColorAnimation->setDuration(200);
    d_ptr->_knobColorAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d_ptr->_knobDiameterAnimation = new QPropertyAnimation(this, "_pKnobDiameter", this);
    d_ptr->_knobDiameterAnimation->setDuration(200);
    d_ptr->_knobDiameterAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d_ptr->_moveAnimation = new QPropertyAnimation(this, "_pKnobCenterX", this);
    d_ptr->_moveAnimation->setDuration(200);
    d_ptr->_moveAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(d_ptr->_bgAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_knobColorAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_knobDiameterAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_moveAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));

    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeToggleSwitch::onThemeChanged);
}

CukeToggleSwitch::~CukeToggleSwitch() = default;

void CukeToggleSwitch::onThemeChanged(CukeThemeType::ThemeMode Mode) {
    CukeHub::onThemeChanged(Mode);

    _pKnobColor = (getThemeMode() == CukeThemeType::Light) ^ d_ptr->_isToggled
                      ? cTheme->getThemeColor(CukeThemeType::Light, CukeThemeType::ToggleSwitchKnob)
                      : cTheme->getThemeColor(CukeThemeType::Dark, CukeThemeType::ToggleSwitchKnob);
    update();
}

void CukeToggleSwitch::setIsToggled(bool isToggled) {
    if (d_ptr->_isToggled == isToggled) return;
    d_ptr->_isToggled = isToggled;
    // 立即跳到对应位置
    _pKnobCenterX = d_ptr->_isToggled ? d_ptr->knobCenterXR : d_ptr->knobCenterXL;
    update();
}

bool CukeToggleSwitch::getIsToggled() const {
    return d_ptr->_isToggled;
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
    d_ptr->_isPressed = true;
    QPointF mousePos = event->pos();
    qreal radius = _pKnobDiameter * 0.5;
    QRectF knobRect(_pKnobCenterX - radius, _pKnobCenterY - radius,
                    _pKnobDiameter, _pKnobDiameter);

    if (knobRect.contains(mousePos)) {
        // 动画到 Press 状态直径
        d_ptr->_knobDiameterAnimation->stop();
        d_ptr->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
        d_ptr->_knobDiameterAnimation->setEndValue(d_ptr->knobDiameterPress);
        d_ptr->_knobDiameterAnimation->start();
    }

    update();
    QWidget::mousePressEvent(event);
}

void CukeToggleSwitch::mouseReleaseEvent(QMouseEvent *event) {
    d_ptr->_isPressed = false;

    // 松开
    QPointF mousePos = event->pos();
    qreal radius = _pKnobDiameter * 0.5;
    QRectF knobRect(_pKnobCenterX - radius, _pKnobCenterY - radius,
                    _pKnobDiameter, _pKnobDiameter);
    d_ptr->_knobDiameterAnimation->stop();
    d_ptr->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
    if (knobRect.contains(mousePos)) {
        d_ptr->_knobDiameterAnimation->setEndValue(d_ptr->knobDiameterHover);
    } else {
        d_ptr->_knobDiameterAnimation->setEndValue(d_ptr->knobDiameter);
    }
    d_ptr->_knobDiameterAnimation->start();

    // 切换状态
    d_ptr->_isToggled = !d_ptr->_isToggled;
    emit toggled(d_ptr->_isToggled);

    d_ptr->_bgAnimation->stop();
    d_ptr->_bgAnimation->setStartValue(_pBgColor);
    d_ptr->_bgAnimation->setEndValue(d_ptr->_isToggled
                                         ? cTheme->getThemeColor(getThemeMode(), CukeThemeType::CheckAlpha)
                                         : cTheme->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha));
    d_ptr->_bgAnimation->start();

    d_ptr->_knobColorAnimation->stop();
    d_ptr->_knobColorAnimation->setStartValue(_pKnobColor);
    d_ptr->_knobColorAnimation->setEndValue((getThemeMode() == CukeThemeType::Light) ^ d_ptr->_isToggled
                                                ? cTheme->getThemeColor(CukeThemeType::Light, CukeThemeType::ToggleSwitchKnob)
                                                : cTheme->getThemeColor(CukeThemeType::Dark, CukeThemeType::ToggleSwitchKnob));
    d_ptr->_knobColorAnimation->start();

    // 使用当前 knobX 作为起点，目标为左右位置
    d_ptr->_moveAnimation->stop();
    d_ptr->_moveAnimation->setStartValue(_pKnobCenterX);
    d_ptr->_moveAnimation->setEndValue(d_ptr->_isToggled ? d_ptr->knobCenterXR : d_ptr->knobCenterXL);
    d_ptr->_moveAnimation->start();

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
    QPointF mousePos = event->pos();

    qreal radius = _pKnobDiameter * 0.5;
    QRectF knobRect(_pKnobCenterX - radius, _pKnobCenterY - radius,
                    _pKnobDiameter, _pKnobDiameter);

    if (knobRect.contains(mousePos)) {
        if (!qFuzzyCompare(_pKnobDiameter + 1.0, d_ptr->knobDiameterHover + 1.0)) {
            d_ptr->_knobDiameterAnimation->stop();
            d_ptr->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
            d_ptr->_knobDiameterAnimation->setEndValue(d_ptr->knobDiameterHover);
            d_ptr->_knobDiameterAnimation->start();
        }
    } else {
        if (!qFuzzyCompare(_pKnobDiameter + 1.0, d_ptr->knobDiameter + 1.0)) {
            d_ptr->_knobDiameterAnimation->stop();
            d_ptr->_knobDiameterAnimation->setStartValue(_pKnobDiameter);
            d_ptr->_knobDiameterAnimation->setEndValue(d_ptr->knobDiameter);
            d_ptr->_knobDiameterAnimation->start();
        }
    }
    QWidget::mouseMoveEvent(event);
}


void CukeToggleSwitch::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    const qreal margin = 4.0;
    const qreal penW = 2.0;
    QRectF contentRect = QRectF(rect()).adjusted(1.0 + penW / 2.0,
                                                 1.0 + penW / 2.0,
                                                 -1.0 - penW / 2.0,
                                                 -1.0 - penW / 2.0);
    const qreal h = contentRect.height();

    // knob 的基本直径
    d_ptr->knobDiameter = qMax<qreal>(0.0, h - 2.0 * margin);
    d_ptr->knobDiameterHover = d_ptr->knobDiameter * 1.2;
    d_ptr->knobDiameterPress = d_ptr->knobDiameter * 0.8;

    // 圆心 Y 用 contentRect 的中心
    _pKnobCenterY = contentRect.top() + h * 0.5;

    // 左右圆心 X
    d_ptr->knobCenterXL = contentRect.left() + margin + d_ptr->knobDiameter * 0.5;
    d_ptr->knobCenterXR = contentRect.right() - margin - d_ptr->knobDiameter * 0.5;

    _pKnobDiameter = d_ptr->knobDiameter;

    if (_pKnobCenterX < 0.0) {
        _pKnobCenterX = d_ptr->_isToggled ? d_ptr->knobCenterXR : d_ptr->knobCenterXL;
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