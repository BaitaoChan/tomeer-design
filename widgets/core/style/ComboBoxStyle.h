#ifndef COMBOBOXSTYLE_H
#define COMBOBOXSTYLE_H
#include <QProxyStyle>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class ComboBoxStyle : public ContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit ComboBoxStyle(QStyle *style = nullptr);
    ~ComboBoxStyle() override;

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


#endif // COMBOBOXSTYLE_H
