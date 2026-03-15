#ifndef CUKETABLEVIEWSTYLE_H
#define CUKETABLEVIEWSTYLE_H
#include <QProxyStyle>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeTableViewStyle : public CukeContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit CukeTableViewStyle(QStyle *style = nullptr);
    ~CukeTableViewStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = nullptr) const override;

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                     const QWidget *widget = nullptr) const override;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override;

};
CUKE_NAMESPACE_END(widget)

#endif // CUKETABLEVIEWSTYLE_H
