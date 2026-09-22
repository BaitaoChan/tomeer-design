#ifndef APP_BAR_H
#define APP_BAR_H
#include <QWidget>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class AppBarPrivate;
class WIDGETS_EXPORT AppBar : public QWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(AppBar)
    TOMEER_Q_PROPERTY_DECL(int, AppBarHeight)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit AppBar(QWidget *parent = nullptr);
    ~AppBar() override;

    void addCustomWidget(QWidget *widget, AppBarType::CustomArea customArea);

    void *object(int key);
    QList<void *> objects();
protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);

    bool eventFilter(QObject *watched, QEvent *event) override;

    void showEvent(QShowEvent *event) override;

};

TOMEER_NAMESPACE_END

#endif // APP_BAR_H
