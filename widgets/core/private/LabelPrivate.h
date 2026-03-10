#ifndef LABELPRIVATE_H
#define LULABELPRIVATE_H
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class Label;
class LabelPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Label)
public:
    explicit LabelPrivate(Label *q);
    ~LabelPrivate() override;
};
CUKE_END_NAMESPACE(widget)


#endif // LABELPRIVATE_H
