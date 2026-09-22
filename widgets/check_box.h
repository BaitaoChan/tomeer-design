#ifndef CHECK_BOX_H
#define CHECK_BOX_H
#include <QCheckBox>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class CheckBoxPrivate;
class WIDGETS_EXPORT CheckBox : public QCheckBox {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(CheckBox)
public:
    explicit CheckBox(QWidget *parent = nullptr);
    ~CheckBox() override;
};
TOMEER_NAMESPACE_END

#endif // CHECK_BOX_H
