#ifndef CHECK_BOX_PRIVATE_H
#define CHECK_BOX_PRIVATE_H
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class CheckBox;
class CheckBoxPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(CheckBox)
public:
    explicit CheckBoxPrivate(CheckBox *q);
    ~CheckBoxPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // CHECK_BOX_PRIVATE_H
