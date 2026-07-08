#ifndef CUKETOOLBARPRIVATE_H
#define CUKETOOLBARPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToolBar;
class ToolBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ToolBar)
public:
    explicit ToolBarPrivate(ToolBar *q);
    ~ToolBarPrivate() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBARPRIVATE_H
