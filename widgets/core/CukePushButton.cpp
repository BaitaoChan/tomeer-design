#include "CukePushButton.h"
#include "CukePushButtonPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukePushButton, int, BorderRadius)

CukePushButton::CukePushButton(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukePushButtonPrivate(this)) {
    setFlat(true);
    _pBorderRadius = 6;
    setStyleSheet("border: none;");
    connect(this, &CukePushButton::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
}

CukePushButton::CukePushButton(QString text, QWidget* parent)
    : CukePushButton(parent) { // 复用上面的构造函数
    setText(text);
}

CukePushButton::~CukePushButton() = default;

void CukePushButton::enterEvent(QEnterEvent *event) {
    d_ptr->_isHovered = true;
    QPushButton::enterEvent(event);
}

void CukePushButton::leaveEvent(QEvent* event) {
    d_ptr->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void CukePushButton::mousePressEvent(QMouseEvent* event) {
    d_ptr->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void CukePushButton::mouseReleaseEvent(QMouseEvent* event) {
    d_ptr->_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void CukePushButton::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = cTheme->getThemeColor(_themeMode, CukeThemeType::DefaultAlpha);
    if (d_ptr->_isPressed) {
        bgColor = cTheme->getThemeColor(_themeMode, CukeThemeType::PressAlpha);
    } else if (d_ptr->_isHovered) {
        bgColor = cTheme->getThemeColor(_themeMode, CukeThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), _pBorderRadius, _pBorderRadius);

    if (!d_ptr->_isPressed) {
        QPen pen;
        pen.setColor(cTheme->getThemeColor(_themeMode, CukeThemeType::Pattern));
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
    option.palette.setColor(QPalette::ButtonText, cTheme->getThemeColor(_themeMode, CukeThemeType::Text));

    if (d_ptr->_isPressed) {
        option.state |= QStyle::State_Sunken;
    }
    if (d_ptr->_isHovered) {
        option.state |= QStyle::State_MouseOver;
    }

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

CUKE_NAMESPACE_END(pub)