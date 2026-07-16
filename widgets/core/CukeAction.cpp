#include "CukeAction.h"
#include "CukeActionPrivate.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
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
    setIconType(icon);
}

Action::~Action() = default;

void Action::setIconType(IconType::Icon pIconType) {
    if (_pIconType != pIconType) {
        _pIconType = pIconType;
        pIconTypeChanged();
        setIcon(CUKE_ICON->getCukeIcon(_pIconType));
    }
}

IconType::Icon Action::getIconType() const {
    return _pIconType;
}

CUKE_NAMESPACE_END(pub)
