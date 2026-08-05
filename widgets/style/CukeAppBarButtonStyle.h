#ifndef CUKEAPPBARBUTTONSTYLE_H
#define CUKEAPPBARBUTTONSTYLE_H
#include <QProxyStyle>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class AppBarButtonStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit AppBarButtonStyle(QStyle *style = nullptr);
    ~AppBarButtonStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;


};

CUKE_NAMESPACE_END

#endif // CUKEAPPBARBUTTONSTYLE_H