#ifndef WINDOWSTYLE_H
#define WINDOWSTYLE_H
#include <QProxyStyle>

#include "Property.h"
#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class WindowStyle : public ContextMixin<QProxyStyle> {
    Q_OBJECT
    explicit WindowStyle(QStyle *style = nullptr);
    ~WindowStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                   const QWidget *widget = nullptr) const override;

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                     const QWidget *widget = nullptr) const override;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override;
};
CUKE_END_NAMESPACE(widget)

#endif // WINDOWSTYLE_H
