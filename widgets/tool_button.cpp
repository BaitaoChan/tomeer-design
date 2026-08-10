#include <QPropertyAnimation>
#include <QHelpEvent>
#include <QMenu>

#include "icon.h"
#include "tool_button.h"
#include "tool_button_private.h"
#include "tool_button_style.h"
#include "tool_tip.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ToolButton, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(ToolButton, qreal, RotateAngle)
TOMEER_Q_PROPERTY_IMPL(ToolButton, ThemeType::ThemeMode, ThemeMode)
TOMEER_Q_PROPERTY_IMPL(ToolButton, GeometryType::SideFlag, SideFlag)
ToolButton::ToolButton(QWidget *parent)
    : QToolButton(parent),
      d_ptr(new ToolButtonPrivate(this)) {
    Q_D(ToolButton);
    setStyle(new ToolButtonStyle());
    setPopupMode(InstantPopup);
    setBorderRadius(4);

    d->_rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    d->_rotateAnim->setDuration(300);
    d->_rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_rotateAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&ToolButton::update));
    connect(this, &ToolButton::pBorderRadiusChanged, this, QOverload<>::of(&ToolButton::update));
    connect(this, &ToolButton::pSideFlagChanged, this, QOverload<>::of(&ToolButton::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &ToolButton::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ToolButton::~ToolButton() = default;

void ToolButton::setIcon(IconType::Icon pIcon) {
    if (_pIcon != pIcon) {
        _pIcon = pIcon;
        pIconChanged();
        setIcon(TOMEER_ICON->getIcon(_pIcon));
    }
}

IconType::Icon ToolButton::getIcon() const {
    return _pIcon;
}

void ToolButton::setMenu(QMenu *menu) {
    Q_D(ToolButton);
    if (QMenu *menu = QToolButton::menu()) {
        disconnect(menu, nullptr, d, nullptr);
    }
    QToolButton::setMenu(menu);

    connect(menu, &QMenu::aboutToShow, d, &ToolButtonPrivate::onMenuShow);
    connect(menu, &QMenu::aboutToHide, d, &ToolButtonPrivate::onMenuHide);
}

QMenu *ToolButton::menu() const {
    return QToolButton::menu();
}

bool ToolButton::event(QEvent *event) {
    if (event->type() == QEvent::ToolTip) {
        const auto helpEvent = dynamic_cast<QHelpEvent *>(event);
        if (!toolTip().isEmpty())
            ToolTip::showText(helpEvent->globalPos(), toolTip(), this);
        else {
            ToolTip::hideText();
            event->ignore();
        }
        return true;
    }
    if (event->type() == QEvent::Leave || event->type() == QEvent::Hide)
        ToolTip::hideText();
    return QToolButton::event(event);
}

void ToolButton::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ToolButton);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END