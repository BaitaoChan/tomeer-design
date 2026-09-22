#ifndef COMBO_BOX_STYLE_H
#define COMBO_BOX_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ComboBoxStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit ComboBoxStyle(QStyle *style = nullptr);
    ~ComboBoxStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
};
TOMEER_NAMESPACE_END


#endif // COMBO_BOX_STYLE_H
