#ifndef CUKEMENUBARSTYLE_H
#define CUKEMENUBARSTYLE_H
#include <QProxyStyle>

#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeMenuBarStyle : public CukeContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit CukeMenuBarStyle(QStyle *style = nullptr);
    ~CukeMenuBarStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = nullptr) const override;

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                     const QWidget *widget = nullptr) const override;

    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter,
                            const QWidget *widget = nullptr) const override;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override;
};
CUKE_END_NAMESPACE(widget)

#endif // CUKEMENUBARSTYLE_H
