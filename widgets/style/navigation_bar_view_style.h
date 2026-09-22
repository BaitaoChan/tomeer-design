#ifndef NAVIGATION_BAR_VIEW_STYLE_H
#define NAVIGATION_BAR_VIEW_STYLE_H

#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()

class NavigationBarViewStyle : public QProxyStyle {
    Q_OBJECT

public:
    explicit NavigationBarViewStyle(QStyle *style = nullptr);
    ~NavigationBarViewStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget = nullptr) const override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_VIEW_STYLE_H
