#ifndef MENU_BAR_STYLE_H
#define MENU_BAR_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class MenuBarStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit MenuBarStyle(QStyle *style = nullptr);
    ~MenuBarStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
};
TOMEER_NAMESPACE_END

#endif // MENU_BAR_STYLE_H