#include "CukeToggleButton.h"
#include "CukeToggleButtonPrivate.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeToggleButton::CukeToggleButton(QWidget *parent)
    : CukeContextMixin(parent), d_ptr(new CukeToggleButtonPrivate(this)) {
    setFlat(true);
    setStyleSheet("border: none;");
    setCheckable(true);
}

CukeToggleButton::CukeToggleButton(const QString &text, QWidget *parent)
    : CukeToggleButton(parent) {
    setText(text);
}

CukeToggleButton::~CukeToggleButton() = default;

void CukeToggleButton::setBorderRadius(const int radius) {
    d_ptr->_borderRadius = radius;
    update();
}

void CukeToggleButton::setIsToggled(const bool isToggled) {
    if (d_ptr->_isToggled != isToggled) {
        d_ptr->_isToggled = isToggled;
        emit toggled(d_ptr->_isToggled);
        update();
    }
}

bool CukeToggleButton::getIsToggled() const {
    return d_ptr->_isToggled;
}

void CukeToggleButton::enterEvent(QEnterEvent *event) {
    d_ptr->_isHovered = true;
    QPushButton::enterEvent(event);
}

void CukeToggleButton::leaveEvent(QEvent *event) {
    d_ptr->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void CukeToggleButton::mousePressEvent(QMouseEvent *event) {
    d_ptr->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void CukeToggleButton::mouseReleaseEvent(QMouseEvent *event) {
    d_ptr->_isPressed = false;
    // 点击切换状态
    if (rect().contains(event->pos())) {
        setIsToggled(!d_ptr->_isToggled);
    }
    QPushButton::mouseReleaseEvent(event);
}

void CukeToggleButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = CukeThemeColor(_themeMode, CukeThemeType::DefaultAlpha);
    if (d_ptr->_isToggled) {
        bgColor = CukeThemeColor(_themeMode, CukeThemeType::CheckAlpha);
    } else if (d_ptr->_isPressed) {
        bgColor = CukeThemeColor(_themeMode, CukeThemeType::PressAlpha);
    } else if (d_ptr->_isHovered) {
        bgColor = CukeThemeColor(_themeMode, CukeThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), d_ptr->_borderRadius, d_ptr->_borderRadius);

    if (!d_ptr->_isPressed && !d_ptr->_isToggled) {
        QPen pen;
        pen.setColor(CukeThemeColor(_themeMode, Pattern));
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
    option.palette.setColor(QPalette::ButtonText, CukeThemeColor(_themeMode, CukeThemeType::Text));

    if (d_ptr->_isPressed) option.state |= QStyle::State_Sunken;
    if (d_ptr->_isHovered) option.state |= QStyle::State_MouseOver;
    if (d_ptr->_isToggled) option.state |= QStyle::State_On;

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

CUKE_NAMESPACE_END(widget)