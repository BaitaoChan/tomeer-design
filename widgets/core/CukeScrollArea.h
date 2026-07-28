#ifndef CUKESCROLLAREA_H
#define CUKESCROLLAREA_H
#include <QScrollArea>

#include "CukeTheme.h"
#include "CukeProperty.h"

class QWheelEvent;
CUKE_NAMESPACE_BEGIN(pub)
class ScrollAreaPrivate;
class CUKE_EXPORT ScrollArea : public QScrollArea {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ScrollArea)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ScrollArea(QWidget *parent = nullptr);
    ~ScrollArea() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCROLLAREA_H