#ifndef CUKEMENUSTYLE_H
#define CUKEMENUSTYLE_H
#include <QProxyStyle>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenuStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit CukeMenuStyle(QStyle *style = nullptr);
    ~CukeMenuStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;

};

CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUSTYLE_H
