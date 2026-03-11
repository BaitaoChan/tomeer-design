#ifndef CUKETABLEITEMDELEGATE_H
#define CUKETABLEITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "CukeContextMixin.h"
#include "CukeLineEdit.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeTableItemDelegate : public CukeContextMixin<QStyledItemDelegate> {
    Q_OBJECT
public:
    explicit CukeTableItemDelegate(QObject *parent = nullptr);
    ~CukeTableItemDelegate() override;

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


#endif // CUKETABLEITEMDELEGATE_H
