#ifndef APP_BAR_PRIVATE_H
#define APP_BAR_PRIVATE_H
#include "property.h"
#include "type.h"


class QHBoxLayout;
class QVBoxLayout;
class QIcon;
class QLabel;
TOMEER_NAMESPACE_BEGIN()
class AppBar;
class Label;
class WidgetRegister;
class AppBarButton;
class ToggleSwitch;
class AppBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(AppBar)
public:
    explicit AppBarPrivate(AppBar *q);
    ~AppBarPrivate() override;

    Q_SLOT void onWindowIconChanged(const QIcon &icon) const;
    Q_SLOT void onWindowTitleChanged(const QString& title) const;
    Q_SLOT void onThemeButtonClicked();
    Q_SLOT void onMinimizeButtonClicked();
    Q_SLOT void onMaximizeButtonClicked();
    Q_SLOT void onCloseButtonClicked();
    Q_SLOT void onHoverChanged();
    Q_SLOT void onWindowStateChanged();

private:
    QHBoxLayout *_mainLayout = nullptr;

    QLabel *_windowIcon = nullptr;
    Label *_windowTitle = nullptr;

    QWidget *_widget = nullptr;
    QHBoxLayout *_layout = nullptr;
    QHBoxLayout *_leftLayout = nullptr;
    QHBoxLayout *_middleLayout = nullptr;
    QHBoxLayout *_rightLayout = nullptr;

    QWidget *_container = nullptr;
    QHBoxLayout *_containerLayout = nullptr;

    AppBarButton *_themeButton = nullptr;
    AppBarButton *_minimizeButton = nullptr;
    AppBarButton *_maximizeButton = nullptr;
    AppBarButton *_closeButton = nullptr;

    WidgetRegister *_widgetRegister = nullptr;
};
TOMEER_NAMESPACE_END

#endif // APP_BAR_PRIVATE_H
