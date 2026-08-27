#ifndef NAVIGATION_BAR_VIEW_H
#define NAVIGATION_BAR_VIEW_H

#include <QTreeWidget>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()

class NavigationBarView : public QTreeWidget {
    Q_OBJECT

public:
    explicit NavigationBarView(QWidget *parent = nullptr);
    ~NavigationBarView() override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_VIEW_H