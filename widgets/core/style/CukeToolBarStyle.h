#ifndef CUKETOOLBARSTYLE_H
#define CUKETOOLBARSTYLE_H
#include <QProxyStyle>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeToolBarStyle : public CukeContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit CukeToolBarStyle(QStyle *style = nullptr);
    ~CukeToolBarStyle() override;
};
CUKE_NAMESPACE_END(widget)

#endif //CUKETOOLBARSTYLE_H
