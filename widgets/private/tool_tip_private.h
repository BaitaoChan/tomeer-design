#ifndef TOOL_TIP_PRIVATE_H
#define TOOL_TIP_PRIVATE_H
#include "property.h"

class QHBoxLayout;
class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class Label;
class ToolTip;
class ToolTipPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ToolTip)
public:
    explicit ToolTipPrivate(ToolTip *q);
    ~ToolTipPrivate() override;

private:
    QHBoxLayout *_layout = nullptr;

    QPropertyAnimation *_opacityAnimation = nullptr;

    Label *_label = nullptr;
    static ToolTip *_toolTip;
};
TOMEER_NAMESPACE_END

#endif // TOOL_TIP_PRIVATE_H