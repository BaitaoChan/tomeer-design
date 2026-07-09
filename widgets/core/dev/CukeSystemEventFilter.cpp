#include "CukeSystemEventFilter.h"

#include "CukeTheme.h"
#ifdef Q_OS_WIN
#include <windows.h>
#endif

CUKE_NAMESPACE_BEGIN(pub)
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

CUKE_NAMESPACE_END(pub)