#ifndef CUKECOMBOBOXPRIVATE_H
#define CUKECOMBOBOXPRIVATE_H
#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(widget)
class CukeComboBox;
class CukeComboBoxPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeComboBox)
public:
    explicit CukeComboBoxPrivate(CukeComboBox *q);
    ~CukeComboBoxPrivate() override;

private:
    QPropertyAnimation *_rotateAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
    QPropertyAnimation *_heightAnim = nullptr;
};
CUKE_NAMESPACE_END(widget)


#endif // CUKECOMBOBOXPRIVATE_H
