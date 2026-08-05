#include "CukeAction.h"
#include "CukeActionPrivate.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN()
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
    setCukeIcon(icon);
}

Action::~Action() = default;

void Action::setCukeIcon(IconType::Icon pCukeIcon) {
    if (_pCukeIcon != pCukeIcon) {
        _pCukeIcon = pCukeIcon;
        pCukeIconChanged();
        setIcon(CUKE_ICON->getCukeIcon(_pCukeIcon));
    }
}

IconType::Icon Action::getCukeIcon() const {
    return _pCukeIcon;
}

CUKE_NAMESPACE_END