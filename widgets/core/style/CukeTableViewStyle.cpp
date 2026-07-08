#include <QHeaderView>
#include <QStyleOption>
#include <QPainterPath>
#include <QPainter>

#include "CukeTableViewStyle.h"
#include "CukeTableView.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(TableViewStyle, int, BorderRadius)
TableViewStyle::TableViewStyle(QStyle *style)
    : QProxyStyle(style),
      _pBorderRadius(6) {

}

TableViewStyle::~TableViewStyle() = default;

void TableViewStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto tableView = qobject_cast<const TableView *>(widget);
    if (element == PE_PanelItemViewRow) {
        if (option->state & State_Selected) {
            painter->save();
            painter->setPen(Qt::NoPen);
            painter->setBrush(CUKE_THEME->getThemeColor(tableView->getThemeMode(), ThemeType::SelectedItem));
            painter->drawRect(option->rect);
            painter->restore();
            return;
        }
        return;
    }


    QProxyStyle::drawPrimitive(element, option, painter, widget);
}

void TableViewStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const {
    const auto tableView = qobject_cast<const TableView *>(widget);
    if (element == CE_ShapedFrame) {
        QRect r = option->rect;
        r.adjust(1, 1, -1, -1);
        painter->save();
        painter->setRenderHints(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(CUKE_THEME->getThemeColor(ThemeType::TableBg));
        painter->drawRoundedRect(r, 6, 6);
        painter->restore();
        return;
    }
    if (element == CE_Header) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRoundedRect(option->rect, 6, 6);
        painter->restore();
        return;
    }
    if (element == CE_HeaderSection) {
        const auto *opt =
                qstyleoption_cast<const QStyleOptionHeader *>(option);
        const auto *header =
                qobject_cast<const QHeaderView *>(widget);

        constexpr int radius = 6;
        const QRect r = option->rect;
        const int section = opt->section;
        const bool isFirst = (section == 0);
        const bool isLast = (section == header->count() - 1);

        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(CUKE_THEME->getThemeColor(tableView->getThemeMode(), ThemeType::HeaderBg));

        if (isFirst && isLast) {
            painter->drawRoundedRect(r, radius, radius);
        } else {
            QPainterPath path;

            if (isFirst) {
                path.moveTo(r.right(), r.top());
                path.lineTo(r.left() + radius, r.top());
                path.quadTo(r.left(), r.top(), r.left(), r.top() + radius);
                path.lineTo(r.left(), r.bottom() - radius);
                path.quadTo(r.left(), r.bottom(), r.left() + radius, r.bottom());
                path.lineTo(r.right(), r.bottom());
            } else if (isLast) {
                path.moveTo(r.left(), r.top());
                path.lineTo(r.right() - radius, r.top());
                path.quadTo(r.right(), r.top(), r.right(), r.top() + radius);
                path.lineTo(r.right(), r.bottom() - radius);
                path.quadTo(r.right(), r.bottom(), r.right() - radius, r.bottom());
                path.lineTo(r.left(), r.bottom());
            } else {
                path.moveTo(r.right(), r.top());
                path.lineTo(r.left(), r.top());
                path.lineTo(r.left(), r.bottom());
                path.lineTo(r.right(), r.bottom());
            }

            path.closeSubpath();
            painter->drawPath(path);
        }

        painter->restore();
        return;
    }


    if (element == CE_HeaderEmptyArea) {
        painter->save();
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(option->rect);
        painter->restore();
        return;
    }
    if (element == CE_HeaderLabel) {
        const auto *opt =
                qstyleoption_cast<const QStyleOptionHeader *>(option);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(CUKE_THEME->getThemeColor(tableView->getThemeMode(), ThemeType::Text));
        painter->drawText(
            option->rect, Qt::AlignVCenter | Qt::AlignHCenter, opt->text);
        painter->restore();
        return;
    }
    QProxyStyle::drawControl(element, option, painter, widget);
}

int TableViewStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const {
    return QProxyStyle::pixelMetric(metric, option, widget);
}

CUKE_NAMESPACE_END(pub)