#include <QPropertyAnimation>

#include "CukeIcon.h"
#include "CukeToolButton.h"
#include "CukeToolButtonPrivate.h"
#include "CukeToolButtonStyle.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeThemeType::ThemeMode, ThemeMode)
CUKE_Q_PROPERTY_IMPL(CukeToolButton, CukeGeometryType::SideFlag, SideFlag)
CukeToolButton::CukeToolButton(QWidget *parent)
    : QToolButton(parent),
      d_ptr(new CukeToolButtonPrivate(this)) {
    Q_D(CukeToolButton);
    setStyle(new CukeToolButtonStyle());
    setBorderRadius(4);

    connect(this, &CukeToolButton::pBorderRadiusChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(this, &CukeToolButton::pSideFlagChanged, this, QOverload<>::of(&CukeToolButton::update));
    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeToolButton::onThemeChanged);
}

CukeToolButton::~CukeToolButton() = default;

void CukeToolButton::setIconType(CukeIconType::Icon pIconType) {
    if (_pIconType != pIconType) {
        _pIconType = pIconType;
        pIconTypeChanged();
        setIcon(cIcon->getCukeIcon(_pIconType));
    }
}

CukeIconType::Icon CukeToolButton::getIconType() const {
    return _pIconType;
}

void CukeToolButton::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToolButton);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)