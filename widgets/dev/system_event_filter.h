#ifndef SYSTEM_EVENT_FILTER_H
#define SYSTEM_EVENT_FILTER_H
#include <QAbstractNativeEventFilter>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class SystemEventFilter : public QAbstractNativeEventFilter {
public:
    explicit SystemEventFilter();
    ~SystemEventFilter() override;

    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;
};
TOMEER_NAMESPACE_END

#endif // SYSTEM_EVENT_FILTER_H
