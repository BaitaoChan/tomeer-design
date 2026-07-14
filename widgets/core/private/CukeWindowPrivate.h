#ifndef CUKEWINDOWPRIVATE_H
#define CUKEWINDOWPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QVBoxLayout;
class QMainWindow;
CUKE_NAMESPACE_BEGIN(pub)
class AppBar;
class Window;
class WindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Window)
    CUKE_Q_PROPERTY_DECL(bool, IsResize)
    CUKE_Q_PROPERTY_DECL(bool, IsDrag)
    CUKE_Q_PROPERTY_DECL(bool, IsApplied)
public:
    explicit WindowPrivate(Window *q = nullptr);
    ~WindowPrivate() override;

private:
    AppBar *_appBar = nullptr;

    void *_widget = nullptr;

    ThemeType::ThemeMode _themeMode = ThemeType::Dark;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEWINDOWPRIVATE_H
