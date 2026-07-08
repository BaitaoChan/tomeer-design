#include "CukePushButton.h"
#include "CukePushButtonPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(PushButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(PushButton, ThemeType::ThemeMode, ThemeMode)
PushButton::PushButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new PushButtonPrivate(this)) {
    Q_D(PushButton);
    setFlat(true);
    _pBorderRadius = 6;
    setStyleSheet("border: none;");
    connect(this, &PushButton::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &PushButton::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

PushButton::PushButton(QString text, QWidget* parent)
    : PushButton(parent) { // 复用上面的构造函数
    setText(text);
}

PushButton::~PushButton() = default;

void PushButton::enterEvent(QEnterEvent *event) {
    Q_D(PushButton);
    d->_isHovered = true;
    QPushButton::enterEvent(event);
}

void PushButton::leaveEvent(QEvent* event) {
    Q_D(PushButton);
    d->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void PushButton::mousePressEvent(QMouseEvent* event) {
    Q_D(PushButton);
    d->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void PushButton::mouseReleaseEvent(QMouseEvent* event) {
    Q_D(PushButton);
    d->_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void PushButton::paintEvent(QPaintEvent* event) {
    Q_D(PushButton);
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = CUKE_THEME->getThemeColor(ThemeType::DefaultAlpha);
    if (d->_isPressed) {
        bgColor = CUKE_THEME->getThemeColor(ThemeType::PressAlpha);
    } else if (d->_isHovered) {
        bgColor = CUKE_THEME->getThemeColor(ThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), _pBorderRadius, _pBorderRadius);

    if (!d->_isPressed) {
        QPen pen;
        pen.setColor(CUKE_THEME->getThemeColor(ThemeType::Pattern));
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
    option.palette.setColor(QPalette::ButtonText, CUKE_THEME->getThemeColor(ThemeType::Text));

    if (d->_isPressed) {
        option.state |= QStyle::State_Sunken;
    }
    if (d->_isHovered) {
        option.state |= QStyle::State_MouseOver;
    }

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

void PushButton::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(PushButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)