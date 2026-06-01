#ifndef CUKETOOLBARSTYLE_H
#define CUKETOOLBARSTYLE_H
#include <QProxyStyle>

#include "CukeObjectMap.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolBarStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit CukeToolBarStyle(QStyle *style = nullptr);
    ~CukeToolBarStyle() override;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBARSTYLE_H
