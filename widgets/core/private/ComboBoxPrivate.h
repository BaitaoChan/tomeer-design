#ifndef COMBOBOXPRIVATE_H
#define COMBOBOXPRIVATE_H
#include "Property.h"

class QPropertyAnimation;
CUKE_BEGIN_NAMESPACE(widget)
class ComboBox;
class ComboBoxPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ComboBox)
public:
    explicit ComboBoxPrivate(ComboBox *q);
    ~ComboBoxPrivate() override;

private:
    QPropertyAnimation *_rotateAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
    QPropertyAnimation *_heightAnim = nullptr;
};
CUKE_END_NAMESPACE(widget)


#endif // COMBOBOXPRIVATE_H
