#ifndef LINEEDITSTYLE_H
#define LINEEDITSTYLE_H
#include <QProxyStyle>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>
#include <QLineEdit>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class LineEditStyle : public ContextMixin<QProxyStyle> {
    Q_OBJECT

public:
    explicit LineEditStyle(QStyle *style = nullptr);
    ~LineEditStyle() override;
};
CUKE_END_NAMESPACE(widget)


#endif // LINEEDITSTYLE_H
