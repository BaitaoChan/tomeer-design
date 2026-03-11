#ifndef CUKEPUSHBUTTONPRIVATE_H
#define CUKEPUSHBUTTONPRIVATE_H
#include "CukeProperty.h"

CUKE_BEGIN_NAMESPACE(widget)
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
CUKE_END_NAMESPACE(widget)



#endif // CUKEPUSHBUTTONPRIVATE_H
