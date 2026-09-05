#ifndef NAVIGATION_BAR_VIEW_H
#define NAVIGATION_BAR_VIEW_H

#include <QModelIndex>
#include <QTreeWidget>

#include "property.h"

class QPropertyAnimation;

TOMEER_NAMESPACE_BEGIN()
class NavigationBarView : public QTreeWidget {
    Q_OBJECT
    TOMEER_Q_PROPERTY_DECL(qreal, RotateAngle)
public:
    explicit NavigationBarView(QWidget *parent = nullptr);
    ~NavigationBarView() override;

    bool isIndexPressed(const QModelIndex &index) const;
    bool isIndexAnimated(const QModelIndex &index) const;

protected:
    bool viewportEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Q_SLOT void onExpanded(const QModelIndex &index);
    Q_SLOT void onCollapsed(const QModelIndex &index);

    QPropertyAnimation *_rotateAnim = nullptr;
    QModelIndex _animatedIndex;
    QModelIndex _pressedIndex;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_VIEW_H