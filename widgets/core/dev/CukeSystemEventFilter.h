#ifndef CUKESYSTEMEVENTFILTER_H
#define CUKESYSTEMEVENTFILTER_H
#include <QAbstractNativeEventFilter>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class SystemEventFilter : public QAbstractNativeEventFilter {
public:
    explicit SystemEventFilter();
    ~SystemEventFilter() override;

    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESYSTEMEVENTFILTER_H
