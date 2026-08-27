#include "navigation_bar_item_delegate.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarItemDelegate::NavigationBarItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

NavigationBarItemDelegate::~NavigationBarItemDelegate() = default;

void NavigationBarItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);
}

QSize NavigationBarItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(option, index);
}

bool NavigationBarItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

TOMEER_NAMESPACE_END