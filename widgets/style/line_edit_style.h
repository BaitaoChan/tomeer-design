#ifndef LINE_EDIT_STYLE_H
#define LINE_EDIT_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class LineEditStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit LineEditStyle(QStyle *style = nullptr);
    ~LineEditStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void polish(QWidget *widget) override;
};
TOMEER_NAMESPACE_END


#endif // LINE_EDIT_STYLE_H