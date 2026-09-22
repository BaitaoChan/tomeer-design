#ifndef TOOL_BAR_PRIVATE_H
#define TOOL_BAR_PRIVATE_H
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class ToolBar;
class ToolBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ToolBar)
public:
    explicit ToolBarPrivate(ToolBar *q);
    ~ToolBarPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // TOOL_BAR_PRIVATE_H
