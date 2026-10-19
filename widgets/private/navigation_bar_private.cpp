#include <QStackedWidget>
#include <QTreeWidgetItem>

#include "navigation_bar_private.h"
#include "navigation_bar.h"

TOMEER_NAMESPACE_BEGIN()

NavigationBarPrivate::NavigationBarPrivate(NavigationBar *q)
    : QObject(q),
      q_ptr(q) {
}

NavigationBarPrivate::~NavigationBarPrivate() = default;

void NavigationBarPrivate::onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
    Q_UNUSED(previous)
    const auto key = current->data(0, NavigationBarType::KeyRole).toString();
    const auto page = _pages.value(key);

    _stackedWidget->setCurrentWidget(page);
}

bool NavigationBarPrivate::_isExpander(const QTreeWidgetItem *node) const {
    const auto nodeType = static_cast<NavigationBarType::NodeType>(node->data(0, NavigationBarType::NodeTypeRole).toInt());
    if (nodeType == NavigationBarType::Expander)
        return true;
    return false;
}

QTreeWidgetItem *NavigationBarPrivate::_createNode(NavigationBarType::NodeType type, const QString &key, const QString &title, IconType::Icon icon) const {
    const auto node = new QTreeWidgetItem;
    node->setData(0, NavigationBarType::KeyRole, key);
    node->setData(0, NavigationBarType::IconRole, icon);
    node->setData(0, NavigationBarType::NodeTypeRole, type);
    node->setText(0, title);
    // 收起态不绘制文字，标题改由 ToolTip 呈现
    node->setToolTip(0, title);
    node->setFlags(type == NavigationBarType::Page ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::ItemIsEnabled);
    return node;
}

TOMEER_NAMESPACE_END
