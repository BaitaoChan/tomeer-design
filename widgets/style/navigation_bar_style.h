#ifndef NAVIGATION_BAR_STYLE_H
#define NAVIGATION_BAR_STYLE_H

#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()

class NavigationBarStyle : public QProxyStyle {
    Q_OBJECT

public:
    explicit NavigationBarStyle(QStyle *style = nullptr);
    ~NavigationBarStyle() override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_STYLE_H