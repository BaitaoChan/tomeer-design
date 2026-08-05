#ifndef CUKESCROLLBARPRIVATE_H
#define CUKESCROLLBARPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class ScrollBar;
class ScrollBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ScrollBar)
public:
    explicit ScrollBarPrivate(ScrollBar *q);
    ~ScrollBarPrivate() override;
};
CUKE_NAMESPACE_END

#endif // CUKESCROLLBARPRIVATE_H