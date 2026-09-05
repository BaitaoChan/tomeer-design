#ifndef NAVIGATION_BAR_NODE_DELEGATE_H
#define NAVIGATION_BAR_NODE_DELEGATE_H

#include <QStyledItemDelegate>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class NavigationBarNodeDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit NavigationBarNodeDelegate(QObject *parent = nullptr);
    ~NavigationBarNodeDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_NODE_DELEGATE_H