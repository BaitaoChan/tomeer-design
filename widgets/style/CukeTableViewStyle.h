#ifndef CUKETABLEVIEWSTYLE_H
#define CUKETABLEVIEWSTYLE_H
#include <QProxyStyle>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class TableViewStyle : public QProxyStyle {
    Q_OBJECT
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
public:
    explicit TableViewStyle(QStyle *style = nullptr);
    ~TableViewStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
};
CUKE_NAMESPACE_END

#endif // CUKETABLEVIEWSTYLE_H