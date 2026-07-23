#ifndef CUKEMAINWINDOW_H
#define CUKEMAINWINDOW_H
#include <QMainWindow>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class AppBar;
class WindowPrivate;
class CUKE_EXPORT Window : public QMainWindow {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Window)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(WindowType::DisplayMode, DisplayMode)
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
CUKE_NAMESPACE_END(pub)

#endif // CUKEMAINWINDOW_H