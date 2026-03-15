#ifndef CUKELINEEDITSTYLE_H
#define CUKELINEEDITSTYLE_H
#include <QProxyStyle>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeLineEditStyle : public CukeContextMixin<QProxyStyle> {
    Q_OBJECT

public:
    explicit CukeLineEditStyle(QStyle *style = nullptr);
    ~CukeLineEditStyle() override;
};
CUKE_NAMESPACE_END(widget)


#endif // CUKELINEEDITSTYLE_H
