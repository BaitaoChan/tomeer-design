#include "table_item_delegate.h"

TOMEER_NAMESPACE_BEGIN()
TableItemDelegate::TableItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

TableItemDelegate::~TableItemDelegate() = default;

QWidget *TableItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    auto *editor = new LineEdit(parent);
    editor->setBorderRadius(0);
    editor->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    return editor;
}

void TableItemDelegate::paint(QPainter *p, const QStyleOptionViewItem &opt, const QModelIndex &index) const {
    p->save();
    p->setRenderHint(QPainter::Antialiasing);
    QRect r = opt.rect;

    // 文本
    p->setPen(TOMEER_THEME->getThemeColor(ThemeType::Text));
    p->setFont(index.data(Qt::FontRole).value<QFont>());

    r.adjust(8, 0, -8, 0);
    p->drawText(r,
                opt.displayAlignment | Qt::AlignHCenter,
                index.data(Qt::DisplayRole).toString());

    p->restore();
}

QSize TableItemDelegate::sizeHint(const QStyleOptionViewItem &opt, const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(opt, index);
}

TOMEER_NAMESPACE_END