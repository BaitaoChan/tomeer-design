#include "CukeToggleSwitch.h"
#include "CukeToggleSwitchPrivate.h"
#include "CukePainter.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitch, CukeThemeType::ThemeMode, ThemeMode)
CukeToggleSwitch::CukeToggleSwitch(QWidget *parent)
    : QWidget(parent),
      d_ptr(new CukeToggleSwitchPrivate(this)) {
    Q_D(CukeToggleSwitch);
    d->_pKnobCenterX = -1;
    setFixedSize(44, 22);
    d->_pKnobColor = CUKE_THEME->getThemeColor(CukeThemeType::ToggleSwitchKnob);
    _pBgColor = d->_isToggled
                    ? (d->_bgColorTo
                           ? *d->_bgColorTo
                           : CUKE_THEME->getThemeColor(CukeThemeType::CheckAlpha))
                    : d->_bgColorFrom
                          ? *d->_bgColorFrom
                          : CUKE_THEME->getThemeColor(CukeThemeType::DefaultAlpha);

    // 属性名与 Q_PROPERTY 中的一致
    d->_bgAnimation = new QPropertyAnimation(this, "_pBgColor", this);
    d->_bgAnimation->setDuration(200);
    d->_bgAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d->_knobColorAnimation = new QPropertyAnimation(d, "_pKnobColor", this);
    d->_knobColorAnimation->setDuration(200);
    d->_knobColorAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d->_knobDiameterAnimation = new QPropertyAnimation(d, "_pKnobDiameter", this);
    d->_knobDiameterAnimation->setDuration(200);
    d->_knobDiameterAnimation->setEasingCurve(QEasingCurve::InOutSine);

    d->_moveAnimation = new QPropertyAnimation(d, "_pKnobCenterX", this);
    d->_moveAnimation->setDuration(200);
    d->_moveAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_bgAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_knobColorAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_knobDiameterAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_moveAnimation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));

    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeToggleSwitch::onThemeChanged);
    connect(CUKE_THEME, &CukeTheme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

CukeToggleSwitch::~CukeToggleSwitch() = default;

void CukeToggleSwitch::bgColorFrom(const QColor color) {
    Q_D(CukeToggleSwitch);
    if (d->_bgColorFrom) {
        delete d->_bgColorFrom;
        d->_bgColorFrom = nullptr;
    }
    d->_bgColorFrom = new QColor(color);
}

void CukeToggleSwitch::bgColorTo(const QColor color) {
    Q_D(CukeToggleSwitch);
    if (d->_bgColorTo) {
        delete d->_bgColorTo;
        d->_bgColorTo = nullptr;
    }
    d->_bgColorTo = new QColor(color);
}

void CukeToggleSwitch::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToggleSwitch);

    d->_pKnobColor = (getThemeMode() == CukeThemeType::Light) || d->_isToggled
                         ? CUKE_THEME->getThemeColor(CukeThemeType::Light, CukeThemeType::ToggleSwitchKnob)
                         : CUKE_THEME->getThemeColor(CukeThemeType::Dark, CukeThemeType::ToggleSwitchKnob);
    _pBgColor = d->_isToggled
                    ? (d->_bgColorTo
                           ? *d->_bgColorTo
                           : CUKE_THEME->getThemeColor(CukeThemeType::CheckAlpha))
                    : d->_bgColorFrom
                          ? *d->_bgColorFrom
                          : CUKE_THEME->getThemeColor(CukeThemeType::DefaultAlpha);
    setThemeMode(mode);
    update();
}

void CukeToggleSwitch::setIsToggled(bool isToggled) {
    Q_D(CukeToggleSwitch);
    if (d->_isToggled == isToggled) return;
    d->_isToggled = isToggled;
    // 立即跳到对应位置
    d->_pKnobCenterX = d->_isToggled ? d->knobCenterXR : d->knobCenterXL;

    _pBgColor = d->_isToggled
                    ? (d->_bgColorTo
                           ? *d->_bgColorTo
                           : CUKE_THEME->getThemeColor(CukeThemeType::CheckAlpha))
                    : d->_bgColorFrom
                          ? *d->_bgColorFrom
                          : CUKE_THEME->getThemeColor(CukeThemeType::DefaultAlpha);
    update();
}

bool CukeToggleSwitch::getIsToggled() {
    Q_D(CukeToggleSwitch);
    return d->_isToggled;
}

void CukeToggleSwitch::setIcon(const QIcon &icon) {
    Q_D(CukeToggleSwitch);
    if (d->_icon) {
        delete d->_icon;
        d->_icon = nullptr;
    }
    d->_icon = new QIcon(icon);
    update();
}
QIcon CukeToggleSwitch::getIcon() {
    Q_D(CukeToggleSwitch);
    return *d->_icon;
}

void CukeToggleSwitch::mousePressEvent(QMouseEvent *event) {
    Q_D(CukeToggleSwitch);
    d->_isPressed = true;
    QPointF mousePos = event->pos();
    qreal radius = d->_pKnobDiameter * 0.5;
    QRectF knobRect(d->_pKnobCenterX - radius, d->_pKnobCenterY - radius,
                    d->_pKnobDiameter, d->_pKnobDiameter);

    if (knobRect.contains(mousePos)) {
        // 动画到 Press 状态直径
        d->_knobDiameterAnimation->stop();
        d->_knobDiameterAnimation->setStartValue(d->_pKnobDiameter);
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
    qreal radius = d->_pKnobDiameter * 0.5;
    QRectF knobRect(d->_pKnobCenterX - radius, d->_pKnobCenterY - radius,
                    d->_pKnobDiameter, d->_pKnobDiameter);
    d->_knobDiameterAnimation->stop();
    d->_knobDiameterAnimation->setStartValue(d->_pKnobDiameter);
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
                                     ? (d->_bgColorTo
                                            ? *d->_bgColorTo
                                            : CUKE_THEME->getThemeColor(CukeThemeType::CheckAlpha))
                                     : d->_bgColorFrom
                                           ? *d->_bgColorFrom
                                           : CUKE_THEME->getThemeColor(CukeThemeType::DefaultAlpha));
    d->_bgAnimation->start();

    d->_knobColorAnimation->stop();
    d->_knobColorAnimation->setStartValue(d->_pKnobColor);
    d->_knobColorAnimation->setEndValue((getThemeMode() == CukeThemeType::Light) || d->_isToggled
                                                ? CUKE_THEME->getThemeColor(CukeThemeType::Light, CukeThemeType::ToggleSwitchKnob)
                                                : CUKE_THEME->getThemeColor(CukeThemeType::Dark, CukeThemeType::ToggleSwitchKnob));
    d->_knobColorAnimation->start();

    // 使用当前 knobX 作为起点，目标为左右位置
    d->_moveAnimation->stop();
    d->_moveAnimation->setStartValue(d->_pKnobCenterX);
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

    qreal radius = d->_pKnobDiameter * 0.5;
    QRectF knobRect(d->_pKnobCenterX - radius, d->_pKnobCenterY - radius,
                    d->_pKnobDiameter, d->_pKnobDiameter);

    if (knobRect.contains(mousePos)) {
        if (!qFuzzyCompare(d->_pKnobDiameter + 1.0, d->knobDiameterHover + 1.0)) {
            d->_knobDiameterAnimation->stop();
            d->_knobDiameterAnimation->setStartValue(d->_pKnobDiameter);
            d->_knobDiameterAnimation->setEndValue(d->knobDiameterHover);
            d->_knobDiameterAnimation->start();
        }
    } else {
        if (!qFuzzyCompare(d->_pKnobDiameter + 1.0, d->knobDiameter + 1.0)) {
            d->_knobDiameterAnimation->stop();
            d->_knobDiameterAnimation->setStartValue(d->_pKnobDiameter);
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
    const qreal borderWidth = height() / 20.0;
    QRectF contentRect = QRectF(rect()).adjusted(1.0 + borderWidth / 2.0,
                                                 1.0 + borderWidth / 2.0,
                                                 -1.0 - borderWidth / 2.0,
                                                 -1.0 - borderWidth / 2.0);
    const qreal h = contentRect.height();

    // knob 的基本直径
    d->knobDiameter = qMax<qreal>(0.0, h - 2.0 * margin);
    d->knobDiameterHover = d->knobDiameter * 1.2;
    d->knobDiameterPress = d->knobDiameter * 0.8;

    // 圆心 Y 用 contentRect 的中心
    d->_pKnobCenterY = contentRect.top() + h * 0.5;

    // 左右圆心 X
    d->knobCenterXL = contentRect.left() + margin + d->knobDiameter * 0.5;
    d->knobCenterXR = contentRect.right() - margin - d->knobDiameter * 0.5;

    d->_pKnobDiameter = d->knobDiameter;

    if (d->_pKnobCenterX < 0.0) {
        d->_pKnobCenterX = d->_isToggled ? d->knobCenterXR : d->knobCenterXL;
    }
}


void CukeToggleSwitch::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    Q_D(CukeToggleSwitch);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const qreal pWidth = height() / 20.0;
    const QRectF pRect = QRectF(rect()).adjusted(1.0 + pWidth / 2.0,
                                                       1.0 + pWidth / 2.0,
                                                       -1.0 - pWidth / 2.0,
                                                       -1.0 - pWidth / 2.0);
    const qreal h = pRect.height();

    // 背景
    p.setPen(Qt::NoPen);
    p.setBrush(_pBgColor);
    p.drawRoundedRect(pRect, h / 2.0, h / 2.0);

    // 边框
    p.setPen(QPen(CUKE_THEME->getThemeColor(CukeThemeType::ToggleSwitchBorder), pWidth));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(pRect, h / 2.0, h / 2.0);

    // 圆钮
    const qreal radius = d->_pKnobDiameter * 0.65;
    p.setPen(Qt::NoPen);
    p.setBrush(isEnabled() ? d->_pKnobColor : CUKE_THEME->getThemeColor(CukeThemeType::TextDisable));
    p.drawEllipse(QPointF(d->_pKnobCenterX, d->_pKnobCenterY), radius, radius);

    // 图标
    if (d->_icon)
        CUKE_PAINTER->drawIcon(QPointF(d->_pKnobCenterX, d->_pKnobCenterY), &p, *d->_icon,
                           QSize(qRound(height() * 0.6 + 1) / 2 * 2, qRound(height() * 0.6 + 1) / 2 * 2));
}

CUKE_NAMESPACE_END(pub)