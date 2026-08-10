#ifndef MENU_STYLE_H
#define MENU_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class MenuStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit MenuStyle(QStyle *style = nullptr);
    ~MenuStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;

};

TOMEER_NAMESPACE_END

#endif // MENU_STYLE_H