#ifndef WINDOW_H
#define WINDOW_H
#include <QMainWindow>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class AppBar;
class WindowPrivate;
class WIDGETS_EXPORT Window : public QMainWindow {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(Window)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    TOMEER_Q_PROPERTY_DECL(WindowType::DisplayMode, DisplayMode)
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;

    AppBar *appBar();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // WINDOW_H