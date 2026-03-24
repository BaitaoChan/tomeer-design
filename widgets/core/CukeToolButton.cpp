#include <QPropertyAnimation>

#include "CukeToolButton.h"

#include <QPushButton.h>

#include "CukeToolButtonPrivate.h"
#include "CukeToolButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, bool, Hover)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, QColor, BgColor)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, bool, BgColorUsedFlag)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeGeometryType::SideFlag, SideFlag)
CukeToolButton::CukeToolButton(QWidget *parent)
    : QToolButton(parent),
      CukeContext(this),
      d_ptr(new CukeToolButtonPrivate(this)) {
    d_ptr->_style = new CukeToolButtonStyle();
    setStyle(d_ptr->_style);

    d_ptr->_bgAnim = new QPropertyAnimation(this, "_pBgColor", this);
    d_ptr->_bgAnim->setDuration(250);
    d_ptr->_bgAnim->setEasingCurve(QEasingCurve::InOutSine);
    connect(d_ptr->_bgAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&CukeToolButton::update));

    connect(this, &CukeToolButton::pBorderRadiusChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pBgColorUsedFlagChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pSideFlagChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pHoverChanged, this, QOverload<>::of(&CukeToolButton::update));
}

CukeToolButton::~CukeToolButton() = default;

void CukeToolButton::bgColorFrom(const QColor color) const {
    d_ptr->_bgColorFrom = new QColor(color);
}

void CukeToolButton::bgColorTo(const QColor color) const {
    d_ptr->_bgColorTo = new QColor(color);
}

void CukeToolButton::enterEvent(QEnterEvent *event) {
    setHover(true);
    if (_pHover) {
        d_ptr->_bgAnim->stop();
        d_ptr->_bgAnim->setStartValue(*d_ptr->_bgColorFrom);
        d_ptr->_bgAnim->setEndValue(*d_ptr->_bgColorTo);
        d_ptr->_bgAnim->start();
    }
    QToolButton::enterEvent(event);
}
void CukeToolButton::leaveEvent(QEvent *event) {
    setHover(false);
    if (!_pHover) {
        d_ptr->_bgAnim->stop();
        d_ptr->_bgAnim->setStartValue(*d_ptr->_bgColorTo);
        d_ptr->_bgAnim->setEndValue(*d_ptr->_bgColorFrom);
        d_ptr->_bgAnim->start();
    }
    QToolButton::leaveEvent(event);
}

CUKE_NAMESPACE_END(pub)