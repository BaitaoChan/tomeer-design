#ifndef TABLEITEMDELEGATE_H
#define TABLEITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "ContextMixin.h"
#include "LineEdit.h"

CUKE_BEGIN_NAMESPACE(widget)
class TableItemDelegate : public ContextMixin<QStyledItemDelegate> {
    Q_OBJECT
public:
    explicit TableItemDelegate(QObject *parent = nullptr);
    ~TableItemDelegate() override;

protected:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void paint(QPainter *p,
               const QStyleOptionViewItem &opt,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &opt,
                   const QModelIndex &index) const override;

};
CUKE_END_NAMESPACE(widget)


#endif // TABLEITEMDELEGATE_H
