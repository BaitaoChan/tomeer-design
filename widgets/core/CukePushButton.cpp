#include "CukePushButton.h"
#include "CukePushButtonPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukePushButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukePushButton, CukeThemeType::ThemeMode, ThemeMode)
CukePushButton::CukePushButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new CukePushButtonPrivate(this)) {
    Q_D(CukePushButton);
    setFlat(true);
    _pBorderRadius = 6;
    setStyleSheet("border: none;");
    connect(this, &CukePushButton::pBorderRadiusChanged, this, QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukePushButton::onThemeChanged);
}

CukePushButton::CukePushButton(QString text, QWidget* parent)
    : CukePushButton(parent) { // 复用上面的构造函数
    setText(text);
}

CukePushButton::~CukePushButton() = default;

void CukePushButton::enterEvent(QEnterEvent *event) {
    Q_D(CukePushButton);
    d->_isHovered = true;
    QPushButton::enterEvent(event);
}

void CukePushButton::leaveEvent(QEvent* event) {
    Q_D(CukePushButton);
    d->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void CukePushButton::mousePressEvent(QMouseEvent* event) {
    Q_D(CukePushButton);
    d->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void CukePushButton::mouseReleaseEvent(QMouseEvent* event) {
    Q_D(CukePushButton);
    d->_isPressed = false;
    QPushButton::mouseReleaseEvent(event);
}

void CukePushButton::paintEvent(QPaintEvent* event) {
    Q_D(CukePushButton);
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha);
    if (d->_isPressed) {
        bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::PressAlpha);
    } else if (d->_isHovered) {
        bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), _pBorderRadius, _pBorderRadius);

    if (!d->_isPressed) {
        QPen pen;
        pen.setColor(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Pattern));
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
    option.palette.setColor(QPalette::ButtonText, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text));

    if (d->_isPressed) {
        option.state |= QStyle::State_Sunken;
    }
    if (d->_isHovered) {
        option.state |= QStyle::State_MouseOver;
    }

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

void CukePushButton::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukePushButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)