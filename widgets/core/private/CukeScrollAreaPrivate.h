#ifndef CUKESCROLLAREAPRIVATE_H
#define CUKESCROLLAREAPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ScrollArea;
class ScrollAreaPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ScrollArea)
public:
    explicit ScrollAreaPrivate(ScrollArea *q);
    ~ScrollAreaPrivate() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCROLLAREAPRIVATE_H