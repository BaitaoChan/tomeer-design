#ifndef SCROLL_BAR_H
#define SCROLL_BAR_H
#include <QScrollBar>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ScrollBarPrivate;
class WIDGETS_EXPORT ScrollBar : public QScrollBar {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ScrollBar)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ScrollBar(QWidget *parent = nullptr);
    explicit ScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~ScrollBar() override;

protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // SCROLL_BAR_H