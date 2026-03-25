#ifndef CUKETABLEVIEWSTYLE_H
#define CUKETABLEVIEWSTYLE_H
#include <QProxyStyle>

#include "CukeHub.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeTableViewStyle : public QProxyStyle, public CukeHub {
    Q_OBJECT
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
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
CUKE_NAMESPACE_END(pub)

#endif // CUKETABLEVIEWSTYLE_H
