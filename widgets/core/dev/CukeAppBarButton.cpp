#include <QPropertyAnimation>

#include "CukeAppBarButton.h"

#include <QPushButton.h>

#include "CukeAppBarButtonPrivate.h"
#include "CukeAppBarButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, bool, Hover)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, bool, Pressed)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, bool, BgColorUsedFlag)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, CukeThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(CukeAppBarButton, CukeGeometryType::SideFlag, SideFlag)
CukeAppBarButton::CukeAppBarButton(QWidget *parent)
    : QToolButton(parent),
      d_ptr(new CukeAppBarButtonPrivate(this)) {
    Q_D(CukeAppBarButton);
    d->_style = new CukeAppBarButtonStyle();
    setStyle(d->_style);

    d->_bgAnim = new QPropertyAnimation(this, "_pBgColor", this);
    d->_bgAnim->setDuration(250);
    d->_bgAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(d->_bgAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&CukeAppBarButton::update));
    connect(this, &CukeAppBarButton::pBorderRadiusChanged, this, QOverload<>::of(&CukeAppBarButton::update));
    connect(this, &CukeAppBarButton::pBgColorUsedFlagChanged, this, QOverload<>::of(&CukeAppBarButton::update));
    connect(this, &CukeAppBarButton::pSideFlagChanged, this, QOverload<>::of(&CukeAppBarButton::update));
    connect(this, &CukeAppBarButton::pHoverChanged, d, &CukeAppBarButtonPrivate::onHoverChanged);
    connect(this, &CukeAppBarButton::pHoverChanged, this, QOverload<>::of(&CukeAppBarButton::update));
    connect(this, &CukeAppBarButton::pPressedChanged, this, QOverload<>::of(&CukeAppBarButton::update));
    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeAppBarButton::onThemeChanged);
}

CukeAppBarButton::~CukeAppBarButton() = default;

void CukeAppBarButton::bgColorFrom(const QColor color) {
    Q_D(CukeAppBarButton);
    if (d->_bgColorFrom) {
        delete d->_bgColorFrom;
        d->_bgColorFrom = nullptr;
    }
    d->_bgColorFrom = new QColor(color);
}

void CukeAppBarButton::bgColorTo(const QColor color) {
    Q_D(CukeAppBarButton);
    if (d->_bgColorTo) {
        delete d->_bgColorTo;
        d->_bgColorTo = nullptr;
    }
    d->_bgColorTo = new QColor(color);
}

void CukeAppBarButton::enterEvent(QEnterEvent *event) {
    setHover(true);
    QToolButton::enterEvent(event);
}
void CukeAppBarButton::leaveEvent(QEvent *event) {
    setHover(false);
    QToolButton::leaveEvent(event);
}

void CukeAppBarButton::mousePressEvent(QMouseEvent *event) {
    setPressed(true);
    QToolButton::mousePressEvent(event);
}

void CukeAppBarButton::mouseReleaseEvent(QMouseEvent *event) {
    setPressed(false);
    QToolButton::mouseReleaseEvent(event);
}

void CukeAppBarButton::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeAppBarButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)