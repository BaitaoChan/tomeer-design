#include <QPropertyAnimation>

#include "app_bar_button.h"

#include <QPushButton.h>

#include "app_bar_button_private.h"
#include "app_bar_button_style.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(AppBarButton, bool, Hover)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, bool, Pressed)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, QColor, BgColor)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, IconType::Icon, Icon)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, bool, BgColorUsedFlag)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, ThemeType::ThemeMode, ThemeMode)
TOMEER_Q_PROPERTY_IMPL(AppBarButton, GeometryType::SideFlag, SideFlag)
AppBarButton::AppBarButton(QWidget *parent)
    : QToolButton(parent),
      d_ptr(new AppBarButtonPrivate(this)) {
    Q_D(AppBarButton);
    setStyle(new AppBarButtonStyle());
    setToolButtonStyle(Qt::ToolButtonIconOnly);
    d->_bgAnim = new QPropertyAnimation(this, "_pBgColor", this);
    d->_bgAnim->setDuration(250);
    d->_bgAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(d->_bgAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pBorderRadiusChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pBgColorUsedFlagChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pSideFlagChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pHoverChanged, d, &AppBarButtonPrivate::onHoverChanged);
    connect(this, &AppBarButton::pIconChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pHoverChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pPressedChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &AppBarButton::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

AppBarButton::~AppBarButton() = default;

void AppBarButton::bgColorFrom(const QColor color) {
    Q_D(AppBarButton);
    if (d->_bgColorFrom) {
        delete d->_bgColorFrom;
        d->_bgColorFrom = nullptr;
    }
    d->_bgColorFrom = new QColor(color);
}

void AppBarButton::bgColorTo(const QColor color) {
    Q_D(AppBarButton);
    if (d->_bgColorTo) {
        delete d->_bgColorTo;
        d->_bgColorTo = nullptr;
    }
    d->_bgColorTo = new QColor(color);
}

void AppBarButton::enterEvent(QEnterEvent *event) {
    setHover(true);
    QToolButton::enterEvent(event);
}
void AppBarButton::leaveEvent(QEvent *event) {
    setHover(false);
    QToolButton::leaveEvent(event);
}

void AppBarButton::mousePressEvent(QMouseEvent *event) {
    setPressed(true);
    QToolButton::mousePressEvent(event);
}

void AppBarButton::mouseReleaseEvent(QMouseEvent *event) {
    setPressed(false);
    QToolButton::mouseReleaseEvent(event);
}

void AppBarButton::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(AppBarButton);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END