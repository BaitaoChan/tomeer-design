#include "action.h"
#include "action_private.h"
#include "icon.h"

TOMEER_NAMESPACE_BEGIN()
Action::Action(QObject *parent)
    : QAction(parent),
      d_ptr(new ActionPrivate(this)) {
}

Action::Action(const QString &text, QObject *parent)
    : Action(parent) {
    setText(text);
}

Action::Action(const QIcon &icon, const QString &text, QObject *parent)
    : Action(text, parent) {
    setIcon(icon);
}

Action::Action(const IconType::Icon &icon, const QString &text, QObject *parent)
    : Action(text, parent) {
    Q_D(Action);
    setIcon(icon);
}

Action::~Action() = default;

void Action::setIcon(IconType::Icon pIcon) {
    if (_pIcon != pIcon) {
        _pIcon = pIcon;
        pIconChanged();
        setIcon(TOMEER_ICON->getIcon(_pIcon));
    }
}

IconType::Icon Action::getIcon() const {
    return _pIcon;
}

TOMEER_NAMESPACE_END