#ifndef CUKEPUSHBUTTONPRIVATE_H
#define CUKEPUSHBUTTONPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukePushButton;
class CukePushButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukePushButton)
public:
    explicit CukePushButtonPrivate(CukePushButton *q);
    ~CukePushButtonPrivate() override;

private:
    bool _isPressed = false;
    bool _isHovered = false;
};
CUKE_NAMESPACE_END(widget)



#endif // CUKEPUSHBUTTONPRIVATE_H
