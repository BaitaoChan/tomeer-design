#ifndef APP_BAR_BUTTON_H
#define APP_BAR_BUTTON_H
#include <QToolButton>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class AppBarButtonPrivate;
class AppBarButton : public QToolButton {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(AppBarButton)
    TOMEER_Q_PROPERTY_DECL(bool, Hover)
    TOMEER_Q_PROPERTY_DECL(bool, Pressed)
    TOMEER_Q_PROPERTY_DECL(QColor, BgColor)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
    TOMEER_Q_PROPERTY_DECL(bool, BgColorUsedFlag)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    TOMEER_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    using QToolButton::setIcon;

    explicit AppBarButton(QWidget *parent = nullptr);
    ~AppBarButton() override;

    void bgColorFrom(QColor color);
    void bgColorTo(QColor color);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // APP_BAR_BUTTON_H