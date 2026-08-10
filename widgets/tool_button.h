#ifndef TOOL_BUTTON_H
#define TOOL_BUTTON_H
#include <QToolButton>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ToolButtonPrivate;
class WIDGETS_EXPORT ToolButton : public QToolButton {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ToolButton)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(qreal, RotateAngle)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    TOMEER_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    using QToolButton::setIcon;

    explicit ToolButton(QWidget *parent = nullptr);
    ~ToolButton() override;

    void setMenu(QMenu *menu);
    QMenu *menu() const;

protected:
    bool event(QEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // TOOL_BUTTON_H