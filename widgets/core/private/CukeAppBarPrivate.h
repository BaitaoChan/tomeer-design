#ifndef CUKEAPPBARPRIVATE_H
#define CUKEAPPBARPRIVATE_H
#include "CukeAppBarPrivate.h"
#include "CukeProperty.h"
#include "CukeType.h"


class QHBoxLayout;
class QVBoxLayout;
class QIcon;
class QLabel;
CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBar;
class CukeLabel;
class CukeObjectMap;
class CukeToolButton;
class CukeToggleSwitch;
class CukeAppBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeAppBar)
public:
    explicit CukeAppBarPrivate(CukeAppBar *q);
    ~CukeAppBarPrivate() override;

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
    CukeLabel *_windowTitle = nullptr;

    QWidget *_widget = nullptr;
    QHBoxLayout *_layout = nullptr;
    QHBoxLayout *_leftLayout = nullptr;
    QHBoxLayout *_middleLayout = nullptr;
    QHBoxLayout *_rightLayout = nullptr;

    QWidget *_container = nullptr;
    QHBoxLayout *_containerLayout = nullptr;

    CukeToolButton *_themeButton = nullptr;
    CukeToolButton *_minimizeButton = nullptr;
    CukeToolButton *_maximizeButton = nullptr;
    CukeToolButton *_closeButton = nullptr;

    CukeObjectMap *_objectMap = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKEAPPBARPRIVATE_H
