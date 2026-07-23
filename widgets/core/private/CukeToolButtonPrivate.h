#ifndef CUKETOOLBUTTONPRIVATE_H
#define CUKETOOLBUTTONPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
class QColor;
CUKE_NAMESPACE_BEGIN(pub)
class ToolButton;
class ToolButtonStyle;
class ToolButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ToolButton)
public:
    explicit ToolButtonPrivate(ToolButton *parent = nullptr);
    ~ToolButtonPrivate() override;

    Q_SLOT void onMenuShow();
    Q_SLOT void onMenuHide();

private:
    QPropertyAnimation *_rotateAnim = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBUTTONPRIVATE_H