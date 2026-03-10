#ifndef MENUBARSTYLE_H
#define MENUBARSTYLE_H
#include <QProxyStyle>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class MenuBarStyle : public ContextMixin<QProxyStyle> {
    Q_OBJECT
public:
    explicit MenuBarStyle(QStyle *style = nullptr);
    ~MenuBarStyle() override;
};
CUKE_END_NAMESPACE(widget)

#endif //MENUBARSTYLE_H
