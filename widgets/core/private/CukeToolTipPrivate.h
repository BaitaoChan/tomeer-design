#ifndef CUKETOOLTIPPRIVATE_H
#define CUKETOOLTIPPRIVATE_H
#include "CukeProperty.h"

class QHBoxLayout;
CUKE_NAMESPACE_BEGIN(pub)
class Label;
class ToolTip;
class ToolTipPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ToolTip)
public:
    explicit ToolTipPrivate(ToolTip *q);
    ~ToolTipPrivate() override;

private:
    QHBoxLayout *_layout = nullptr;

    Label *_label = nullptr;
    static ToolTip *_toolTip;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLTIPPRIVATE_H