#ifndef TABLE_VIEW_STYLE_H
#define TABLE_VIEW_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class TableViewStyle : public QProxyStyle {
    Q_OBJECT
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
public:
    explicit TableViewStyle(QStyle *style = nullptr);
    ~TableViewStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
};
TOMEER_NAMESPACE_END

#endif // TABLE_VIEW_STYLE_H