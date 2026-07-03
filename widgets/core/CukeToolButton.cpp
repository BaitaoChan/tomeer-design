#include <QPropertyAnimation>
#include <QMenu>

#include "CukeIcon.h"
#include "CukeToolButton.h"
#include "CukeToolButtonPrivate.h"
#include "CukeToolButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, qreal, RotateAngle)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeGeometryType::SideFlag, SideFlag)
CukeToolButton::CukeToolButton(QWidget *parent)
    : QToolButton(parent),
      d_ptr(new CukeToolButtonPrivate(this)) {
    Q_D(CukeToolButton);
    setStyle(new CukeToolButtonStyle());
    setPopupMode(InstantPopup);
    setBorderRadius(4);

    d->_rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    d->_rotateAnim->setDuration(300);
    d->_rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_rotateAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pBorderRadiusChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pSideFlagChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeToolButton::onThemeChanged);
}

CukeToolButton::~CukeToolButton() = default;

void CukeToolButton::setIconType(CukeIconType::Icon pIconType) {
    if (_pIconType != pIconType) {
        _pIconType = pIconType;
        pIconTypeChanged();
        setIcon(CUKE_ICON->getCukeIcon(_pIconType));
    }
}

CukeIconType::Icon CukeToolButton::getIconType() const {
    return _pIconType;
}

void CukeToolButton::setMenu(QMenu *menu) {
    Q_D(CukeToolButton);
    if (QMenu *menu = QToolButton::menu()) {
        disconnect(menu, nullptr, d, nullptr);
    }
    QToolButton::setMenu(menu);

    connect(menu, &QMenu::aboutToShow, d, &CukeToolButtonPrivate::onMenuShow);
    connect(menu, &QMenu::aboutToHide, d, &CukeToolButtonPrivate::onMenuHide);
}

QMenu *CukeToolButton::menu() const {
    return QToolButton::menu();
}

void CukeToolButton::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToolButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)