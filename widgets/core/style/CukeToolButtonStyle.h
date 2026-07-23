#ifndef CUKETOOLBUTTONSTYLE_H
#define CUKETOOLBUTTONSTYLE_H
#include <QProxyStyle>

#include "CukeProperty.h"
#include "CukeToolButton.h"

CUKE_NAMESPACE_BEGIN(pub)
    class ToolButtonStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit ToolButtonStyle(QStyle *style = nullptr);
    ~ToolButtonStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawComplexControl(ComplexControl control, const QStyleOptionComplex *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    QSize sizeFromContents(ContentsType type, const QStyleOption *option, const QSize &size, const QWidget *widget) const override;
};

CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTONSTYLE_H