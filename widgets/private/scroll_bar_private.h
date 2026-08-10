#ifndef SCROLL_BAR_PRIVATE_H
#define SCROLL_BAR_PRIVATE_H
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ScrollBar;
class ScrollBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ScrollBar)
public:
    explicit ScrollBarPrivate(ScrollBar *q);
    ~ScrollBarPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // SCROLL_BAR_PRIVATE_H