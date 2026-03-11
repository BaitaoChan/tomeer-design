#ifndef CUKELINEEDITSTYLE_H
#define CUKELINEEDITSTYLE_H
#include <QProxyStyle>

#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeLineEditStyle : public CukeContextMixin<QProxyStyle> {
    Q_OBJECT

public:
    explicit CukeLineEditStyle(QStyle *style = nullptr);
    ~CukeLineEditStyle() override;
};
CUKE_END_NAMESPACE(widget)


#endif // CUKELINEEDITSTYLE_H
