#include "PushButton.h"
#include "PushButtonPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CUKE_Q_PROPERTY_IMPL(PushButton, int, BorderRadius)

PushButton::PushButton(QWidget *parent)
    : ContextMixin(parent),
      d_ptr(new PushButtonPrivate(this)) {
    setFlat(true);
    _pBorderRadius = 6;
    setStyleSheet("border: none;");
    connect(this, &PushButton::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
}

PushButton::PushButton(QString text, QWidget* parent)
    : PushButton(parent) { // 复用上面的构造函数
    setText(text);
}

PushButton::~PushButton() = default;

void PushButton::enterEvent(QEnterEvent *event) {
    d_ptr->_isHovered = true;
    QPushButton::enterEvent(event);
}

void PushButton::leaveEvent(QEvent* event) {
    d_ptr->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void PushButton::mousePressEvent(QMouseEvent* event) {
    d_ptr->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void PushButton::mouseReleaseEvent(QMouseEvent* event) {
    d_ptr->_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void PushButton::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = pThemeColor(_themeMode, DefaultAlpha);
    if (d_ptr->_isPressed) {
        bgColor = pThemeColor(_themeMode, PressAlpha);
    } else if (d_ptr->_isHovered) {
        bgColor = pThemeColor(_themeMode, HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), _pBorderRadius, _pBorderRadius);

    if (!d_ptr->_isPressed) {
        QPen pen;
        pen.setColor(pThemeColor(_themeMode, Pattern));
        pen.setWidthF(1.6);
        painter.setPen(pen);

        int shadowBorder = 2;
        QRect r = rect();

        painter.drawLine(
            r.x() + _pBorderRadius,
            r.height() - shadowBorder,
            r.width() - _pBorderRadius,
            r.height() - shadowBorder
        );
    }

    // 绘制文字和图标
    QStyleOptionButton option;
    option.initFrom(this);
    option.text = text();
    option.icon = icon();
    option.iconSize = icon().isNull() ? QSize() : this->iconSize();

    // 用当前的文字颜色
    option.palette.setColor(QPalette::ButtonText, pThemeColor(_themeMode, Text));

    if (d_ptr->_isPressed) {
        option.state |= QStyle::State_Sunken;
    }
    if (d_ptr->_isHovered) {
        option.state |= QStyle::State_MouseOver;
    }

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

CUKE_END_NAMESPACE(widget)