#include "CukeAction.h"
#include "CukeActionPrivate.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(Action, IconType::Icon, IconType)
Action::Action(QObject *parent)
    : QAction(parent),
      d_ptr(new ActionPrivate(this)) {
}

Action::Action(const QString &text, QObject *parent)
    : Action(parent) {
    setText(text);
}

Action::Action(const IconType::Icon &icon, const QString &text, QObject *parent)
    : Action(text, parent) {
    setIconType(icon);
}

Action::~Action() = default;

CUKE_NAMESPACE_END(pub)
