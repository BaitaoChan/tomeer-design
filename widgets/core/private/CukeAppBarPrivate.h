#ifndef CUKEAPPBARPRIVATE_H
#define CUKEAPPBARPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"


class QHBoxLayout;
class QVBoxLayout;
class QIcon;
class QLabel;
CUKE_NAMESPACE_BEGIN(pub)
class AppBar;
class Label;
class WidgetRegister;
class AppBarButton;
class ToggleSwitch;
class AppBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(AppBar)
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
CUKE_NAMESPACE_END(pub)

#endif //CUKEAPPBARPRIVATE_H