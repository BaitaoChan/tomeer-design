#ifndef SCROLL_BAR_STYLE_H
#define SCROLL_BAR_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ScrollBarStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit ScrollBarStyle(QStyle *style = nullptr);
    ~ScrollBarStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QRect subControlRect(ComplexControl control, const QStyleOptionComplex *option, SubControl subControl, const QWidget *widget = nullptr) const override;
    SubControl hitTestComplexControl(ComplexControl control, const QStyleOptionComplex *option, const QPoint &position, const QWidget *widget = nullptr) const override;
};
TOMEER_NAMESPACE_END

#endif // SCROLL_BAR_STYLE_H
