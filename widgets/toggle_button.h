#ifndef TOGGLE_BUTTON_H
#define TOGGLE_BUTTON_H
#include <QAbstractButton>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ToggleButtonPrivate;
class WIDGETS_EXPORT ToggleButton : public QAbstractButton {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ToggleButton)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    TOMEER_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    using QAbstractButton::setIcon;

    explicit ToggleButton(QWidget *parent = nullptr);
    explicit ToggleButton(const QString &text, QWidget *parent = nullptr);
    explicit ToggleButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    explicit ToggleButton(const IconType::Icon &icon, const QString &text, QWidget *parent = nullptr);
    ~ToggleButton() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // TOGGLE_BUTTON_H