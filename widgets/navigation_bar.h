#ifndef NAVIGATION_BAR_H
#define NAVIGATION_BAR_H
#include <QWidget>
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class NavigationBarPrivate;
class WIDGETS_EXPORT NavigationBar : public QWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(NavigationBar)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar() override;
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_H