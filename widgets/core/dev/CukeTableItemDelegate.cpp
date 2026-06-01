#include "CukeTableItemDelegate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeTableItemDelegate::CukeTableItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

CukeTableItemDelegate::~CukeTableItemDelegate() = default;

QWidget *CukeTableItemDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const {
    auto *editor = new CukeLineEdit(parent);
    editor->setBorderRadius(0);
    editor->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    return editor;
}

void CukeTableItemDelegate::paint(QPainter *p,
                           const QStyleOptionViewItem &opt,
                           const QModelIndex &index) const {
    p->save();
    p->setRenderHint(QPainter::Antialiasing);
    QRect r = opt.rect;

    // 文本
    p->setPen(cTheme->getThemeColor(cTheme->getThemeMode(), CukeThemeType::Text));
    p->setFont(index.data(Qt::FontRole).value<QFont>());

    r.adjust(8, 0, -8, 0);
    p->drawText(r,
                opt.displayAlignment | Qt::AlignHCenter,
                index.data(Qt::DisplayRole).toString());

    p->restore();
}

QSize CukeTableItemDelegate::sizeHint(const QStyleOptionViewItem &opt,
                               const QModelIndex &index) const {
    return QStyledItemDelegate::sizeHint(opt, index);
}

CUKE_NAMESPACE_END(pub)