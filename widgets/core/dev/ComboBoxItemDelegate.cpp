#include "ComboBoxItemDelegate.h"

CUKE_BEGIN_NAMESPACE(widget)
ComboBoxItemDelegate::ComboBoxItemDelegate(QObject *parent)
    : ContextMixin(parent) {
}

ComboBoxItemDelegate::~ComboBoxItemDelegate() = default;

void ComboBoxItemDelegate::paint(QPainter *painter,
                                   const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    const QRect r = option.rect;

    // 背景
    if (option.state & QStyle::State_Selected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(pThemeColor(_themeMode, ComboBoxItem));
        painter->drawRoundedRect(r.adjusted(8, 2, -2, -2), 4, 4);
    }

    // 激光指示
    if (option.state & QStyle::State_Selected) {
        const QRect lr(r.left() + 10, r.top() + 4, 3, r.height() - 8);
        painter->setPen(Qt::NoPen);
        painter->setBrush(pThemeColor(pTheme->getThemeMode(), Check));
        painter->drawRoundedRect(lr, 2, 2);
    }

    // 文本
    painter->setPen(pThemeColor(_themeMode, Text));
    painter->drawText(r.adjusted(16, 0, -2, 0), Qt::AlignVCenter | Qt::AlignLeft,
                      index.data(Qt::DisplayRole).toString());

    painter->restore();
}

QSize ComboBoxItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const {
    return QSize(0, 30);
}

CUKE_END_NAMESPACE(widget)