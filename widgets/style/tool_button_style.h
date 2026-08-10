#ifndef TOOL_BUTTON_STYLE_H
#define TOOL_BUTTON_STYLE_H
#include <QProxyStyle>

#include "property.h"
#include "tool_button.h"

TOMEER_NAMESPACE_BEGIN()
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

TOMEER_NAMESPACE_END

#endif // TOOL_BUTTON_STYLE_H