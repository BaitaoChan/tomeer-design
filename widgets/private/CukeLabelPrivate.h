#ifndef CUKELABELPRIVATE_H
#define CUKELABELPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN()
class Label;
class LabelPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Label)
public:
    explicit LabelPrivate(Label *q);
    ~LabelPrivate() override;
};
CUKE_NAMESPACE_END


#endif // CUKELABELPRIVATE_H