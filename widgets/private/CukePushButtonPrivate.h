#ifndef CUKEPUSHBUTTONPRIVATE_H
#define CUKEPUSHBUTTONPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class PushButton;
class PushButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(PushButton)
public:
    explicit PushButtonPrivate(PushButton *q);
    ~PushButtonPrivate() override;
};
CUKE_NAMESPACE_END

#endif // CUKEPUSHBUTTONPRIVATE_H