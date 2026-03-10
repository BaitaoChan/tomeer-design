#ifndef TABLEVIEWSTYLE_H
#define TABLEVIEWSTYLE_H
#include <QHeaderView>
#include <QProxyStyle>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class TableViewStyle : public ContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit TableViewStyle(QStyle *style = nullptr);
    ~TableViewStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget = nullptr) const override;

    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                     const QWidget *widget = nullptr) const override;

    int pixelMetric(PixelMetric metric, const QStyleOption *option = nullptr,
                    const QWidget *widget = nullptr) const override;

};
CUKE_END_NAMESPACE(widget)


#endif // TABLEVIEWSTYLE_H
