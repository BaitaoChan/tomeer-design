#ifndef CHECKBOXPRIVATE_H
#define CHECKBOXPRIVATE_H
#include "Property.h"

class QVariantAnimation;
CUKE_BEGIN_NAMESPACE(widget)
class CheckBox;
class CheckBoxPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CheckBox)
public:
    explicit CheckBoxPrivate(CheckBox *q);
    ~CheckBoxPrivate() override;

private:
    QVariantAnimation* _checkAnim = nullptr;
};
CUKE_END_NAMESPACE(widget)
#endif // CHECKBOXPRIVATE_H
