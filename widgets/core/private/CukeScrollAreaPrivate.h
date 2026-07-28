#ifndef CUKESCROLLAREAPRIVATE_H
#define CUKESCROLLAREAPRIVATE_H
#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(pub)
class ScrollArea;
class ScrollAreaPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ScrollArea)
public:
    explicit ScrollAreaPrivate(ScrollArea *q);
    ~ScrollAreaPrivate() override;

private:
    QPropertyAnimation *_verScrollAnim = nullptr;
    QPropertyAnimation *_horScrollAnim = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCROLLAREAPRIVATE_H