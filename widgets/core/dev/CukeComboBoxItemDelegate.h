#ifndef CUKECOMBOBOXITEMDELEGATE_H
#define CUKECOMBOBOXITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "CukeContext.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeComboBoxItemDelegate : public QStyledItemDelegate, public CukeContext {
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
CUKE_NAMESPACE_END(pub)


#endif // CUKECOMBOBOXITEMDELEGATE_H
