#ifndef COMBO_BOX_PRIVATE_H
#define COMBO_BOX_PRIVATE_H
#include "property.h"
#include "type.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class ComboBox;
class ComboBoxView;
class ComboBoxPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ComboBox)
    TOMEER_Q_PROPERTY_DECL(bool, IsPopup)
public:
    explicit ComboBoxPrivate(ComboBox *q);
    ~ComboBoxPrivate() override;

private:
    ComboBoxView *_view = nullptr;
    QPropertyAnimation *_rotateAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
    QPropertyAnimation *_heightAnim = nullptr;
};
TOMEER_NAMESPACE_END


#endif // COMBO_BOX_PRIVATE_H