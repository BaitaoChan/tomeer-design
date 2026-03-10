#include "ToggleButton.h"
#include "ToggleButtonPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
ToggleButton::ToggleButton(QWidget *parent)
    : ContextMixin(parent), d_ptr(new ToggleButtonPrivate(this)) {
    setFlat(true);
    setStyleSheet("border: none;");
    setCheckable(true);
}

ToggleButton::ToggleButton(const QString &text, QWidget *parent)
    : ToggleButton(parent) {
    setText(text);
}

ToggleButton::~ToggleButton() = default;

void ToggleButton::setBorderRadius(const int radius) {
    d_ptr->_borderRadius = radius;
    update();
}

void ToggleButton::setIsToggled(const bool isToggled) {
    if (d_ptr->_isToggled != isToggled) {
        d_ptr->_isToggled = isToggled;
        emit toggled(d_ptr->_isToggled);
        update();
    }
}

bool ToggleButton::getIsToggled() const {
    return d_ptr->_isToggled;
}

void ToggleButton::enterEvent(QEnterEvent *event) {
    d_ptr->_isHovered = true;
    QPushButton::enterEvent(event);
}

void ToggleButton::leaveEvent(QEvent *event) {
    d_ptr->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void ToggleButton::mousePressEvent(QMouseEvent *event) {
    d_ptr->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void ToggleButton::mouseReleaseEvent(QMouseEvent *event) {
    d_ptr->_isPressed = false;
    // 点击切换状态
    if (rect().contains(event->pos())) {
        setIsToggled(!d_ptr->_isToggled);
    }
    QPushButton::mouseReleaseEvent(event);
}

void ToggleButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = pThemeColor(_themeMode, ThemeType::DefaultAlpha);
    if (d_ptr->_isToggled) {
        bgColor = pThemeColor(_themeMode, ThemeType::CheckAlpha);
    } else if (d_ptr->_isPressed) {
        bgColor = pThemeColor(_themeMode, ThemeType::PressAlpha);
    } else if (d_ptr->_isHovered) {
        bgColor = pThemeColor(_themeMode, ThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), d_ptr->_borderRadius, d_ptr->_borderRadius);

    if (!d_ptr->_isPressed && !d_ptr->_isToggled) {
        QPen pen;
        pen.setColor(pThemeColor(_themeMode, Pattern));
        pen.setWidthF(1.6);
        painter.setPen(pen);

        int shadowBorder = 2;
        QRect r = rect();

        painter.drawLine(
            r.x() + d_ptr->_borderRadius,
            r.height() - shadowBorder,
            r.width() - d_ptr->_borderRadius,
            r.height() - shadowBorder
        );
    }

    QStyleOptionButton option;
    option.initFrom(this);
    option.text = text();
    option.icon = icon();
    option.iconSize = icon().isNull() ? QSize() : this->iconSize();
    option.palette.setColor(QPalette::ButtonText, pThemeColor(_themeMode, ThemeType::Text));

    if (d_ptr->_isPressed) option.state |= QStyle::State_Sunken;
    if (d_ptr->_isHovered) option.state |= QStyle::State_MouseOver;
    if (d_ptr->_isToggled) option.state |= QStyle::State_On;

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

CUKE_END_NAMESPACE(widget)