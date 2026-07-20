#ifndef CUKESCROLLAREASTYLE_H
#define CUKESCROLLAREASTYLE_H
#include <QProxyStyle>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ScrollAreaStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit ScrollAreaStyle(QStyle *style = nullptr);
    ~ScrollAreaStyle() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCROLLAREASTYLE_H