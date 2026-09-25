#ifndef CHECK_BOX_STYLE_H
#define CHECK_BOX_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class CheckBoxStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit CheckBoxStyle(QStyle *style = nullptr);
    ~CheckBoxStyle() override;

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption* option, const QWidget* widget) const override;

};
TOMEER_NAMESPACE_END

#endif // CHECK_BOX_STYLE_H
