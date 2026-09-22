#ifndef COMBO_BOX_ITEM_DELEGATE_H
#define COMBO_BOX_ITEM_DELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ComboBoxItemDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit ComboBoxItemDelegate(QObject *parent = nullptr);
    ~ComboBoxItemDelegate() override;

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
TOMEER_NAMESPACE_END


#endif // COMBO_BOX_ITEM_DELEGATE_H
