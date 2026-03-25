#ifndef CUKEWINDOWSTYLE_H
#define CUKEWINDOWSTYLE_H
#include <QProxyStyle>

#include "CukeHub.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeWindowStyle : public QProxyStyle, public CukeHub {
    Q_OBJECT
public:
    explicit CukeWindowStyle(QStyle *style = nullptr);
    ~CukeWindowStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                     const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter,
                            const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEWINDOWSTYLE_H
