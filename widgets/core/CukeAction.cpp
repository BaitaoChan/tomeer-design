#include "CukeAction.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeAction, CukeIconType::Icon, IconType)
CukeAction::CukeAction(QObject *parent)
    : QAction(parent) {
}

CukeAction::CukeAction(const QString &text, QObject *parent)
    : CukeAction(parent) {
    setText(text);
}

CukeAction::CukeAction(const CukeIconType::Icon &icon, const QString &text, QObject *parent)
    : CukeAction(text, parent) {
    setIconType(icon);
}

CukeAction::~CukeAction() = default;

CUKE_NAMESPACE_END(pub)
