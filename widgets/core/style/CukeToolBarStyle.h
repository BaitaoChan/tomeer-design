#ifndef CUKETOOLBARSTYLE_H
#define CUKETOOLBARSTYLE_H
#include <QProxyStyle>

#include "CukeObjectMap.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolBarStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit CukeToolBarStyle(QStyle *style = nullptr);
    ~CukeToolBarStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBARSTYLE_H
