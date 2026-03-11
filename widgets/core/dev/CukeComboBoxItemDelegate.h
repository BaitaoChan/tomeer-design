#ifndef CUKECOMBOBOXITEMDELEGATE_H
#define CUKECOMBOBOXITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeComboBoxItemDelegate : public CukeContextMixin<QStyledItemDelegate> {
    Q_OBJECT
public:
    explicit CukeComboBoxItemDelegate(QObject *parent = nullptr);
    ~CukeComboBoxItemDelegate() override;

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;
};
CUKE_END_NAMESPACE(widget)


#endif // CUKECOMBOBOXITEMDELEGATE_H
