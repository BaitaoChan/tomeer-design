#include <QPropertyAnimation>

#include "CukeToolButton.h"

#include <QPushButton.h>

#include "CukeToolButtonPrivate.h"
#include "CukeToolButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, bool, Hover)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, bool, Pressed)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, bool, BgColorUsedFlag)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeGeometryType::SideFlag, SideFlag)
CukeToolButton::CukeToolButton(QWidget *parent)
    : QToolButton(parent),
      d_ptr(new CukeToolButtonPrivate(this)) {
    Q_D(CukeToolButton);
    d->_style = new CukeToolButtonStyle();
    setStyle(d->_style);

    d->_bgAnim = new QPropertyAnimation(this, "_pBgColor", this);
    d->_bgAnim->setDuration(250);
    d->_bgAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(d->_bgAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pBorderRadiusChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pBgColorUsedFlagChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pSideFlagChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pHoverChanged, d, &CukeToolButtonPrivate::onHoverChanged);
    connect(this, &CukeToolButton::pHoverChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pPressedChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeToolButton::onThemeChanged);
}

CukeToolButton::~CukeToolButton() = default;

void CukeToolButton::bgColorFrom(const QColor color) {
    Q_D(CukeToolButton);
    if (d->_bgColorFrom) {
        delete d->_bgColorFrom;
        d->_bgColorFrom = nullptr;
    }
    d->_bgColorFrom = new QColor(color);
}

void CukeToolButton::bgColorTo(const QColor color) {
    Q_D(CukeToolButton);
    if (d->_bgColorTo) {
        delete d->_bgColorTo;
        d->_bgColorTo = nullptr;
    }
    d->_bgColorTo = new QColor(color);
}

void CukeToolButton::enterEvent(QEnterEvent *event) {
    setHover(true);
    QToolButton::enterEvent(event);
}
void CukeToolButton::leaveEvent(QEvent *event) {
    setHover(false);
    QToolButton::leaveEvent(event);
}

void CukeToolButton::mousePressEvent(QMouseEvent *event) {
    setPressed(true);
    QToolButton::mousePressEvent(event);
}

void CukeToolButton::mouseReleaseEvent(QMouseEvent *event) {
    setPressed(false);
    QToolButton::mouseReleaseEvent(event);
}

void CukeToolButton::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToolButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)