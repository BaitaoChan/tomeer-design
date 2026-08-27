#ifndef NAVIGATION_BAR_STYLE_H
#define NAVIGATION_BAR_STYLE_H

#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()

class NavigationBarStyle : public QProxyStyle {
    Q_OBJECT

public:
    explicit NavigationBarStyle(QStyle *style = nullptr);
    ~NavigationBarStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_STYLE_H