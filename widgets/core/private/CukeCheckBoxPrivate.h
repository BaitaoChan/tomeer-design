#ifndef CUKECHECKBOXPRIVATE_H
#define CUKECHECKBOXPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QVariantAnimation;
CUKE_NAMESPACE_BEGIN(pub)
class CukeCheckBox;
class CukeCheckBoxPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeCheckBox)
public:
    explicit CukeCheckBoxPrivate(CukeCheckBox *q);
    ~CukeCheckBoxPrivate() override;

    Q_SLOT void onToggled(bool checked);

private:
    QVariantAnimation* _checkAnim = nullptr;
};
CUKE_NAMESPACE_END(pub)
#endif // CUKECHECKBOXPRIVATE_H
