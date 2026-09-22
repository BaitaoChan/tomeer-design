#ifndef APP_BAR_BUTTON_STYLE_H
#define APP_BAR_BUTTON_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
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

TOMEER_NAMESPACE_END

#endif // APP_BAR_BUTTON_STYLE_H
