#ifndef TOOL_BUTTON_PRIVATE_H
#define TOOL_BUTTON_PRIVATE_H
#include "property.h"
#include "type.h"

class QPropertyAnimation;
class QColor;
TOMEER_NAMESPACE_BEGIN()
class ToolButton;
class ToolButtonStyle;
class ToolButtonPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ToolButton)
public:
    explicit ToolButtonPrivate(ToolButton *parent = nullptr);
    ~ToolButtonPrivate() override;

    Q_SLOT void onMenuShow();
    Q_SLOT void onMenuHide();

private:
    QPropertyAnimation *_rotateAnim = nullptr;
};
TOMEER_NAMESPACE_END

#endif // TOOL_BUTTON_PRIVATE_H
