#include "CukeToggleButton.h"
#include "CukeToggleButtonPrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToggleButton, CukeThemeType::ThemeMode, ThemeMode)
CukeToggleButton::CukeToggleButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new CukeToggleButtonPrivate(this)) {
    Q_D(CukeToggleButton);
    setFlat(true);
    setStyleSheet("border: none;");
    setCheckable(true);
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeToggleButton::onThemeChanged);
}

CukeToggleButton::CukeToggleButton(const QString &text, QWidget *parent)
    : CukeToggleButton(parent) {
    setText(text);
}

CukeToggleButton::~CukeToggleButton() = default;

void CukeToggleButton::setBorderRadius(const int radius) {
    Q_D(CukeToggleButton);
    d->_borderRadius = radius;
    update();
}

void CukeToggleButton::setIsToggled(const bool isToggled) {
    Q_D(CukeToggleButton);
    if (d->_isToggled != isToggled) {
        d->_isToggled = isToggled;
        emit toggled(d->_isToggled);
        update();
    }
}

bool CukeToggleButton::getIsToggled() {
    Q_D(CukeToggleButton);
    return d->_isToggled;
}

void CukeToggleButton::enterEvent(QEnterEvent *event) {
    Q_D(CukeToggleButton);
    d->_isHovered = true;
    QPushButton::enterEvent(event);
}

void CukeToggleButton::leaveEvent(QEvent *event) {
    Q_D(CukeToggleButton);
    d->_isHovered = false;
    QPushButton::leaveEvent(event);
}

void CukeToggleButton::mousePressEvent(QMouseEvent *event) {
    Q_D(CukeToggleButton);
    d->_isPressed = true;
    QPushButton::mousePressEvent(event);
}

void CukeToggleButton::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(CukeToggleButton);
    d->_isPressed = false;
    // 点击切换状态
    if (rect().contains(event->pos())) {
        setIsToggled(!d->_isToggled);
    }
    QPushButton::mouseReleaseEvent(event);
}

void CukeToggleButton::paintEvent(QPaintEvent *event) {
    Q_D(CukeToggleButton);
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha);
    if (d->_isToggled) {
        bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::CheckAlpha);
    } else if (d->_isPressed) {
        bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::PressAlpha);
    } else if (d->_isHovered) {
        bgColor = CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::HoverAlpha);
    }

    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(rect(), d->_borderRadius, d->_borderRadius);

    if (!d->_isPressed && !d->_isToggled) {
        QPen pen;
        pen.setColor(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Pattern));
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
    option.palette.setColor(QPalette::ButtonText, CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text));

    if (d->_isPressed) option.state |= QStyle::State_Sunken;
    if (d->_isHovered) option.state |= QStyle::State_MouseOver;
    if (d->_isToggled) option.state |= QStyle::State_On;

    style()->drawControl(QStyle::CE_PushButtonLabel, &option, &painter, this);
}

void CukeToggleButton::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToggleButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)