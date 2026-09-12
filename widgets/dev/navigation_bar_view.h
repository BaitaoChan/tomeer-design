#ifndef NAVIGATION_BAR_VIEW_H
#define NAVIGATION_BAR_VIEW_H
#include <QTreeWidget>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class NavigationBarViewPrivate;
class NavigationBarView : public QTreeWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(NavigationBarView)
    TOMEER_Q_PROPERTY_DECL(qreal, RotateAngle)
public:
    explicit NavigationBarView(QWidget *parent = nullptr);
    ~NavigationBarView() override;

    bool isPressed(const QModelIndex &index) const;
    bool isToggling(const QModelIndex &index) const;

protected:
    bool viewportEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;
    void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paintEvent(QPaintEvent *event) override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_VIEW_H