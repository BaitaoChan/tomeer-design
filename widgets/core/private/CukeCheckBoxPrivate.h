#ifndef CUKECHECKBOXPRIVATE_H
#define CUKECHECKBOXPRIVATE_H
#include "CukeProperty.h"

class QVariantAnimation;
CUKE_BEGIN_NAMESPACE(widget)
class CukeCheckBox;
class CukeCheckBoxPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeCheckBox)
public:
    explicit CukeCheckBoxPrivate(CukeCheckBox *q);
    ~CukeCheckBoxPrivate() override;

private:
    QVariantAnimation* _checkAnim = nullptr;
};
CUKE_END_NAMESPACE(widget)
#endif // CUKECHECKBOXPRIVATE_H
