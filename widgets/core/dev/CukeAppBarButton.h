#ifndef CUKEAPPBARBUTTON_H
#define CUKEAPPBARBUTTON_H
#include <QToolButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class AppBarButtonPrivate;
class AppBarButton : public QToolButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(AppBarButton)
    CUKE_Q_PROPERTY_DECL(bool, Hover)
    CUKE_Q_PROPERTY_DECL(bool, Pressed)
    CUKE_Q_PROPERTY_DECL(QColor, BgColor)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(bool, BgColorUsedFlag)
    CUKE_Q_PROPERTY_DECL(IconType::Icon, IconType)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
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
CUKE_NAMESPACE_END(pub)

#endif // CUKEAPPBARBUTTON_H