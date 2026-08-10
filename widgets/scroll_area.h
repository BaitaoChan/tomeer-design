#ifndef SCROLL_AREA_H
#define SCROLL_AREA_H
#include <QScrollArea>

#include "theme.h"
#include "property.h"

class QWheelEvent;
TOMEER_NAMESPACE_BEGIN()
class ScrollAreaPrivate;
class WIDGETS_EXPORT ScrollArea : public QScrollArea {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ScrollArea)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // SCROLL_AREA_H