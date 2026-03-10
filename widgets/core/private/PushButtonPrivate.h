#ifndef PUSHBUTTONPRIVATE_H
#define PUSHBUTTONPRIVATE_H
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class PushButton;
class PushButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(PushButton)
public:
    explicit PushButtonPrivate(PushButton *q);
    ~PushButtonPrivate() override;

private:
    bool _isPressed = false;
    bool _isHovered = false;
};
CUKE_END_NAMESPACE(widget)



#endif // PUSHBUTTONPRIVATE_H
