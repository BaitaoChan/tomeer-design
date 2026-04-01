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

private:
    QHBoxLayout *_layout = nullptr;

    CukeLabel *_windowTitle = nullptr;
    QLabel *_windowIcon = nullptr;

    QWidget *_container = nullptr;
    QHBoxLayout *_containerLayout = nullptr;

    CukeToolButton *_themeButton = nullptr;
    CukeToolButton *_minimizeButton = nullptr;
    CukeToolButton *_maximizeButton = nullptr;
    CukeToolButton *_closeButton = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKEAPPBARPRIVATE_H
