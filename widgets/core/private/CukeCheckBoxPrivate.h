#ifndef CUKECHECKBOXPRIVATE_H
#define CUKECHECKBOXPRIVATE_H
#include "CukeProperty.h"

class QVariantAnimation;
CUKE_NAMESPACE_BEGIN(widget)
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
CUKE_NAMESPACE_END(widget)
#endif // CUKECHECKBOXPRIVATE_H
