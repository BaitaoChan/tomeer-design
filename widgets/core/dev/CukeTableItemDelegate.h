#ifndef CUKETABLEITEMDELEGATE_H
#define CUKETABLEITEMDELEGATE_H
#include <QStyledItemDelegate>
#include <QPainter>

#include "CukeContext.h"
#include "CukeProperty.h"
#include "CukeLineEdit.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeTableItemDelegate : public QStyledItemDelegate, public CukeContext {
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
CUKE_NAMESPACE_END(pub)


#endif // CUKETABLEITEMDELEGATE_H
