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
};
CUKE_NAMESPACE_END(pub)


#endif // CUKELINEEDITSTYLE_H