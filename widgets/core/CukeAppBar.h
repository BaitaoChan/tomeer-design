#ifndef CUKEAPPBAR_H
#define CUKEAPPBAR_H
#include <QWidget>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBarPrivate;
class CUKE_EXPORT CukeAppBar : public QWidget {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeAppBar)
    CUKE_Q_PROPERTY_DECL(int, AppBarHeight)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeAppBar(QWidget *parent = nullptr);
    ~CukeAppBar() override;

    void addCustomWidget(QWidget *widget, CukeAppBarType::CustomArea customArea);

    void *object(int key);
    QList<void *> objects();
protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);

    bool eventFilter(QObject *watched, QEvent *event) override;

    void showEvent(QShowEvent *event) override;

};

CUKE_NAMESPACE_END(pub)

#endif // CUKEAPPBAR_H
