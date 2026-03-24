#ifndef CUKELINEEDITSTYLE_H
#define CUKELINEEDITSTYLE_H
#include <QProxyStyle>

#include "CukeContext.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeLineEditStyle : public QProxyStyle, public CukeContext {
    Q_OBJECT

public:
    explicit CukeLineEditStyle(QStyle *style = nullptr);
    ~CukeLineEditStyle() override;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKELINEEDITSTYLE_H
