#ifndef CUKELINEEDITSTYLE_H
#define CUKELINEEDITSTYLE_H
#include <QProxyStyle>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class LineEditStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit LineEditStyle(QStyle *style = nullptr);
    ~LineEditStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void polish(QWidget *widget) override;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKELINEEDITSTYLE_H