#ifndef NAVIGATION_BAR_ITEM_DELEGATE_H
#define NAVIGATION_BAR_ITEM_DELEGATE_H

#include <QStyledItemDelegate>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()

class NavigationBarItemDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit NavigationBarItemDelegate(QObject *parent = nullptr);
    ~NavigationBarItemDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_ITEM_DELEGATE_H