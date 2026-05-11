#ifndef CUKEMENUBARSTYLE_H
#define CUKEMENUBARSTYLE_H
#include <QProxyStyle>

#include "CukeScope.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenuBarStyle : public QProxyStyle, public CukeScope {
    Q_OBJECT
public:
    explicit CukeMenuBarStyle(QStyle *style = nullptr);
    ~CukeMenuBarStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUBARSTYLE_H
