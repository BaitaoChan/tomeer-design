#ifndef CUKECOMBOBOXITEMDELEGATE_H
#define CUKECOMBOBOXITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class ComboBoxItemDelegate : public QStyledItemDelegate {
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
CUKE_NAMESPACE_END


#endif // CUKECOMBOBOXITEMDELEGATE_H