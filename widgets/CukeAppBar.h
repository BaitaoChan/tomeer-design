#ifndef CUKEAPPBAR_H
#define CUKEAPPBAR_H
#include <QWidget>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN()
class AppBarPrivate;
class CUKE_EXPORT AppBar : public QWidget {
    Q_OBJECT
    CUKE_DECLARE_DPTR(AppBar)
    CUKE_Q_PROPERTY_DECL(int, AppBarHeight)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
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

CUKE_NAMESPACE_END

#endif // CUKEAPPBAR_H