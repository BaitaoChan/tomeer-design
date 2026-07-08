#include "CukeToggleButton.h"
#include "CukeToggleButtonPrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(ToggleButton, ThemeType::ThemeMode, ThemeMode)
ToggleButton::ToggleButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new ToggleButtonPrivate(this)) {
    Q_D(ToggleButton);
    setFlat(true);
    setStyleSheet("border: none;");
    setCheckable(true);
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &ToggleButton::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ToggleButton::ToggleButton(const QString &text, QWidget *parent)
    : ToggleButton(parent) {
    setText(text);
}

ToggleButton::~ToggleButton() = default;

void ToggleButton::setBorderRadius(const int radius) {
    Q_D(ToggleButton);
    d->_borderRadius = radius;
    update();
}

void ToggleButton::setIsToggled(const bool isToggled) {
    Q_D(ToggleButton);
    if (d->_isToggled != isToggled) {
        d->_isToggled = isToggled;
        emit toggled(d->_isToggled);
        update();
    }
}

bool ToggleButton::getIsToggled() {
    Q_D(ToggleButton);
    return d->_isToggled;
}

void ToggleButton::enterEvent(QEnterEvent *event) {
    Q_D(ToggleButton);
    d->_isHovered = true;
    QPushButton::enterEvent(event);
}

void ToggleButton::leaveEvent(QEvent *event) {
    Q_D(ToggleButton);
    d->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void ToggleButton::mousePressEvent(QMouseEvent *event) {
    Q_D(ToggleButton);
    d->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void ToggleButton::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(ToggleButton);
    d->_isPressed = false;
    // 点击切换状态
    if (rect().contains(event->pos())) {
        setIsToggled(!d->_isToggled);
    }
    QPushButton::mouseReleaseEvent(event);
}

void ToggleButton::paintEvent(QPaintEvent *event) {
    Q_D(ToggleButton);
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = CUKE_THEME->getThemeColor(ThemeType::DefaultAlpha);
    if (d->_isToggled) {
        bgColor = CUKE_THEME->getThemeColor(ThemeType::CheckAlpha);
    } else if (d->_isPressed) {
        bgColor = CUKE_THEME->getThemeColor(ThemeType::PressAlpha);
    } else if (d->_isHovered) {
        bgColor = CUKE_THEME->getThemeColor(ThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), d->_borderRadius, d->_borderRadius);

    if (!d->_isPressed && !d->_isToggled) {
        QPen pen;
        pen.setColor(CUKE_THEME->getThemeColor(ThemeType::Pattern));
        pen.setWidthF(1.6);
        painter.setPen(pen);

        int shadowBorder = 2;
        QRect r = rect();

        painter.drawLine(
            r.x() + d->_borderRadius,
            r.height() - shadowBorder,
            r.width() - d->_borderRadius,
            r.height() - shadowBorder
        );
    }

    QStyleOptionButton option;
    option.initFrom(this);
    option.text = text();
    option.icon = icon();
    option.iconSize = icon().isNull() ? QSize() : this->iconSize();
    option.palette.setColor(QPalette::ButtonText, CUKE_THEME->getThemeColor(ThemeType::Text));

    if (d->_isPressed) option.state |= QStyle::State_Sunken;
    if (d->_isHovered) option.state |= QStyle::State_MouseOver;
    if (d->_isToggled) option.state |= QStyle::State_On;

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

void ToggleButton::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ToggleButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)