#ifndef CUKESCROLLAREA_H
#define CUKESCROLLAREA_H
#include <QScrollArea>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ScrollAreaPrivate;
class CUKE_EXPORT ScrollArea : public QScrollArea {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ScrollArea)
public:
    explicit ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCROLLAREA_H