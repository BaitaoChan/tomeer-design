#ifndef CUKEPUSHBUTTONPRIVATE_H
#define CUKEPUSHBUTTONPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
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
CUKE_NAMESPACE_END(pub)



#endif // CUKEPUSHBUTTONPRIVATE_H
