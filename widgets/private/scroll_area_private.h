#ifndef SCROLL_AREA_PRIVATE_H
#define SCROLL_AREA_PRIVATE_H
#include "property.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class ScrollArea;
class ScrollAreaPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ScrollArea)
public:
    explicit ScrollAreaPrivate(ScrollArea *q);
    ~ScrollAreaPrivate() override;

private:
    QPropertyAnimation *_verScrollAnim = nullptr;
    QPropertyAnimation *_horScrollAnim = nullptr;
};
TOMEER_NAMESPACE_END

#endif // SCROLL_AREA_PRIVATE_H
