#ifndef WINDOW_PRIVATE_H
#define WINDOW_PRIVATE_H
#include "property.h"
#include "type.h"

class QVBoxLayout;
class QMainWindow;
TOMEER_NAMESPACE_BEGIN()
class AppBar;
class Window;
class WindowPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(Window)
    TOMEER_Q_PROPERTY_DECL(bool, IsResize)
    TOMEER_Q_PROPERTY_DECL(bool, IsDrag)
    TOMEER_Q_PROPERTY_DECL(bool, IsApplied)
public:
    explicit WindowPrivate(Window *q = nullptr);
    ~WindowPrivate() override;

private:
    AppBar *_appBar = nullptr;

    void *_widget = nullptr;

    ThemeType::ThemeMode _themeMode = ThemeType::Dark;
};
TOMEER_NAMESPACE_END

#endif // WINDOW_PRIVATE_H