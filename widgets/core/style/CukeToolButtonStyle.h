#ifndef CUKETOOLBUTTONSTYLE_H
#define CUKETOOLBUTTONSTYLE_H
#include <QProxyStyle>

#include "CukeObjectMap.h"
#include "CukeProperty.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
    class CukeToolButtonStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit CukeToolButtonStyle(QStyle *style = nullptr);
    ~CukeToolButtonStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
};

CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTONSTYLE_H
