#ifndef CHECK_BOX_H
#define CHECK_BOX_H
#include <QCheckBox>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class CheckBoxPrivate;
class WIDGETS_EXPORT CheckBox : public QCheckBox {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(CheckBox)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    using QAbstractButton::setIcon;

    explicit CheckBox(QWidget *parent = nullptr);
    explicit CheckBox(const QString &text, QWidget *parent = nullptr);
    ~CheckBox() override;

protected:
    bool hitButton(const QPoint &pos) const override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // CHECK_BOX_H
