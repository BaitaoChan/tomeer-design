#include "system_event_filter.h"

#include "theme.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif

TOMEER_NAMESPACE_BEGIN()
SystemEventFilter::SystemEventFilter() = default;

SystemEventFilter::~SystemEventFilter() = default;

bool SystemEventFilter::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) {
    Q_UNUSED(eventType)
    Q_UNUSED(result)
#ifdef Q_OS_WIN
    const auto pMsg = static_cast<MSG *>(message);
#else
    Q_UNUSED(message)
#endif
    return false;
}

TOMEER_NAMESPACE_END