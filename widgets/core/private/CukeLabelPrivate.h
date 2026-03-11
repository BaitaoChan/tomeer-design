#ifndef CUKELABELPRIVATE_H
#define CUKELABELPRIVATE_H
#include "CukeProperty.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeLabel;
class CukeLabelPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeLabel)
public:
    explicit CukeLabelPrivate(CukeLabel *q);
    ~CukeLabelPrivate() override;
};
CUKE_END_NAMESPACE(widget)


#endif // CUKELABELPRIVATE_H
