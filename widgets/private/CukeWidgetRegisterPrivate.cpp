#include "CukeWidgetRegisterPrivate.h"
#include "CukeWidgetRegister.h"

CUKE_NAMESPACE_BEGIN()
WidgetRegisterPrivate::WidgetRegisterPrivate(WidgetRegister *q)
    : q_ptr(q) {
}

WidgetRegisterPrivate::~WidgetRegisterPrivate() = default;

CUKE_NAMESPACE_END