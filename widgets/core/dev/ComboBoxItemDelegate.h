#ifndef COMBOBOXITEMDELEGATE_H
#define COMBOBOXITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class ComboBoxItemDelegate : public ContextMixin<QStyledItemDelegate> {
    Q_OBJECT
public:
    explicit ComboBoxItemDelegate(QObject *parent = nullptr);
    ~ComboBoxItemDelegate() override;

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};
CUKE_END_NAMESPACE(widget)


#endif // COMBOBOXITEMDELEGATE_H
