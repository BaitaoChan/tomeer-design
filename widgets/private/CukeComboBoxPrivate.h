#ifndef CUKECOMBOBOXPRIVATE_H
#define CUKECOMBOBOXPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN()
class ComboBox;
class ComboBoxPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ComboBox)
    CUKE_Q_PROPERTY_DECL(bool, IsPopup)
public:
    explicit ComboBoxPrivate(ComboBox *q);
    ~ComboBoxPrivate() override;

private:
    QPropertyAnimation *_rotateAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
    QPropertyAnimation *_heightAnim = nullptr;
};
CUKE_NAMESPACE_END


#endif // CUKECOMBOBOXPRIVATE_H