#ifndef TABLE_ITEM_DELEGATE_H
#define TABLE_ITEM_DELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "property.h"
#include "line_edit.h"

TOMEER_NAMESPACE_BEGIN()
class TableItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit TableItemDelegate(QObject *parent = nullptr);
    ~TableItemDelegate() override;

protected:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &opt, const QModelIndex &index) const override;

};
TOMEER_NAMESPACE_END


#endif // TABLE_ITEM_DELEGATE_H