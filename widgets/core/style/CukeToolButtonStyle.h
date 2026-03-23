#ifndef CUKETOOLBUTTONSTYLE_H
#define CUKETOOLBUTTONSTYLE_H
#include <QProxyStyle>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolButtonStyle : public CukeContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit CukeToolButtonStyle(QStyle *style = nullptr);
    ~CukeToolButtonStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
};

CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTONSTYLE_H
