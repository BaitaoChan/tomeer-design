#include "navigation_bar_node_delegate.h"
#include "navigation_bar_view.h"
#include "painter.h"
#include "theme.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarNodeDelegate::NavigationBarNodeDelegate(QObject *parent)
    : QStyledItemDelegate(parent) {
}

NavigationBarNodeDelegate::~NavigationBarNodeDelegate() = default;

void NavigationBarNodeDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    const QRect r = option.rect.adjusted(4, 2, -4, -2);
    const auto view = qobject_cast<const NavigationBarView *>(option.widget);

    // 背景
    if (option.state & QStyle::State_Enabled) {
        painter->setPen(Qt::NoPen);
        if (option.state & QStyle::State_Selected)
            painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::NavigationNodeSelected));
        else if (view->isPressed(index))
            painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::PressAlpha));
        else if (option.state & QStyle::State_MouseOver)
            painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::HoverAlpha));
        painter->drawRoundedRect(r, 4, 4);
    }

    const auto nodeType = static_cast<NavigationBarType::NodeType>(index.data(NavigationBarType::NodeTypeRole).toInt());

    // 选中指示
    // if (option.state & QStyle::State_Enabled) {
    //     if (option.state & QStyle::State_Selected) {
    //         if (nodeType == NavigationBarType::Page) {
    //             painter->setPen(Qt::NoPen);
    //             painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::CheckAlpha));
    //             QRect iRect(0, 0, 3, 16);
    //             iRect.moveCenter(r.center());
    //             iRect.moveLeft(r.left());
    //             TOMEER_PAINTER->drawRoundedRect(iRect, painter, 1.5, 1.5);
    //         }
    //     }
    // }

    if (option.state & QStyle::State_Enabled) {
        painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::Text));
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::Text));
    } else {
        painter->setPen(TOMEER_THEME->getThemeColor(ThemeType::TextDisable));
        painter->setBrush(TOMEER_THEME->getThemeColor(ThemeType::TextDisable));
    }

    // 图标
    const QSize iSize = view->iconSize();
    const QRect iRect(r.left() + 12, r.center().y() - iSize.height() / 2, iSize.width(), iSize.height());
    const auto icon = static_cast<IconType::Icon>(index.data(NavigationBarType::IconRole).toInt());

    if (icon != IconType::None) {
        painter->save();
        QFont font("tomeer");
        font.setPixelSize(iSize.height());
        painter->setFont(font);
        painter->drawText(iRect, Qt::AlignCenter, QString(QChar(icon)));
        painter->restore();
    }

    QRect tRect = r.adjusted(iRect.right() - r.left() + 10, 0, -8, 0);
    if (nodeType == NavigationBarType::Expander) {
        // 判断拓展节点是否包含子节点
        if (index.model()->hasChildren(index)) {
            tRect.adjust(0, 0, -iSize.width() - 12, 0);

            // 展开箭头
            qreal rotateAngle = 0.0;
            if (view->isExpanded(index))
                rotateAngle = 180.0;
            if (view->isToggling(index))
                rotateAngle = view->getRotateAngle();

            const QRect aRect(r.right() - iSize.width() - 12, r.top(), iSize.width() + 12, r.height());
            painter->save();
            QFont font("tomeer");
            font.setPixelSize(iSize.height());

            QPainterPath path;
            path.addText(QPointF(0, 0), font, QString(QChar(IconType::ChevronDown)));

            QTransform transform;
            transform.translate(aRect.center().x(), aRect.center().y());
            transform.rotate(rotateAngle);
            transform.translate(-path.boundingRect().center().x(), -path.boundingRect().center().y());

            painter->setPen(Qt::NoPen);
            painter->setTransform(transform, true);
            painter->drawPath(path);
            painter->restore();
        }
    }

    // 文本
    painter->setFont(option.font);
    painter->drawText(tRect, Qt::AlignVCenter | Qt::AlignLeft, option.fontMetrics.elidedText(index.data(Qt::DisplayRole).toString(), Qt::ElideRight, tRect.width()));

    painter->restore();
}

QSize NavigationBarNodeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return {0, 40};
}

TOMEER_NAMESPACE_END
