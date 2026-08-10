#ifndef LABEL_PRIVATE_H
#define LABEL_PRIVATE_H
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class Label;
class LabelPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(Label)
public:
    explicit LabelPrivate(Label *q);
    ~LabelPrivate() override;
};
TOMEER_NAMESPACE_END


#endif // LABEL_PRIVATE_H