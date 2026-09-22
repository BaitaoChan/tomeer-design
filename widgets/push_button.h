#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H
#include <QAbstractButton>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class PushButtonPrivate;
class WIDGETS_EXPORT PushButton : public QAbstractButton {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(PushButton)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    TOMEER_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    using QAbstractButton::setIcon;

    explicit PushButton(QWidget *parent = nullptr);
    explicit PushButton(const QString &text, QWidget *parent = nullptr);
    explicit PushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    explicit PushButton(const IconType::Icon &icon, const QString &text, QWidget *parent = nullptr);
    ~PushButton() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // PUSH_BUTTON_H
