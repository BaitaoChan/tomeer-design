#include <QPropertyAnimation>

#include "CukeAppBarButton.h"

#include <QPushButton.h>

#include "CukeAppBarButtonPrivate.h"
#include "CukeAppBarButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(AppBarButton, bool, Hover)
CUKE_Q_PROPERTY_IMPL(AppBarButton, bool, Pressed)
CUKE_Q_PROPERTY_IMPL(AppBarButton, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(AppBarButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(AppBarButton, bool, BgColorUsedFlag)
CUKE_Q_PROPERTY_IMPL(AppBarButton, IconType::Icon, CukeIcon)
CUKE_Q_PROPERTY_IMPL(AppBarButton, ThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(AppBarButton, GeometryType::SideFlag, SideFlag)
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
    connect(this, &AppBarButton::pCukeIconChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pHoverChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(this, &AppBarButton::pPressedChanged, this, QOverload<>::of(&AppBarButton::update));
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &AppBarButton::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
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

CUKE_NAMESPACE_END(pub)