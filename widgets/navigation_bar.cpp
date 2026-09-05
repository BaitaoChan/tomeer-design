#include "navigation_bar.h"

#include <QHBoxLayout>
#include <QList>
#include <QStackedWidget>
#include <QStyleOption>
#include <QStylePainter>
#include <QTreeWidgetItem>

#include "navigation_bar_node_delegate.h"
#include "navigation_bar_private.h"
#include "navigation_bar_style.h"
#include "navigation_bar_view.h"
#include "navigation_bar_view_style.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()

TOMEER_Q_PROPERTY_IMPL(NavigationBar, ThemeType::ThemeMode, ThemeMode)
NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new NavigationBarPrivate(this)) {
    Q_D(NavigationBar);

    setStyle(new NavigationBarStyle(style()));

    d->_view = new NavigationBarView(this);
    d->_view->setStyle(new NavigationBarViewStyle(d->_view->style()));
    d->_view->setItemDelegate(new NavigationBarNodeDelegate(d->_view));
    d->_view->setFixedWidth(220);

    d->_stackedWidget = new QStackedWidget(this);

    auto layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->_view);
    layout->addWidget(d->_stackedWidget, 1);

    connect(d->_view, &QTreeWidget::currentItemChanged, this, [this, d](const QTreeWidgetItem *current, QTreeWidgetItem *) {
        if (!current)
            return;

        const auto key = current->data(0, NavigationBarType::KeyRole).toString();
        const auto page = d->_pages.value(key);
        if (!page)
            return;

        d->_stackedWidget->setCurrentWidget(page);
        emit currentKeyChanged(key);
    });
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &NavigationBar::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
    connect(TOMEER_THEME, &Theme::themeColorChanged, d->_view->viewport(), QOverload<>::of(&QWidget::update));

    setThemeMode(TOMEER_THEME->getThemeMode());
}

NavigationBar::~NavigationBar() = default;

bool NavigationBar::addPageNode(QWidget *page, const QString &key, const QString &title, IconType::Icon icon, const QString &parentKey) {
    Q_D(NavigationBar);
    if (!page || key.isEmpty() || d->_nodes.contains(key))
        return false;
    if (d->_stackedWidget->indexOf(page) >= 0)
        return false;

    const auto parentNode = parentKey.isEmpty() ? nullptr : d->_nodes.value(parentKey);
    if (!parentKey.isEmpty() && !d->_isExpander(parentNode))
        return false;

    const auto node = d->_createNode(NavigationBarType::Page, key, title, icon);
    if (parentNode)
        parentNode->addChild(node);
    else
        d->_view->addTopLevelItem(node);

    d->_nodes.insert(key, node);
    d->_pages.insert(key, page);
    d->_stackedWidget->addWidget(page);
    return true;
}

bool NavigationBar::addExpanderNode(const QString &key,
                                    const QString &title,
                                    IconType::Icon icon,
                                    const QString &parentKey) {
    Q_D(NavigationBar);
    if (key.isEmpty() || d->_nodes.contains(key))
        return false;

    const auto parentNode = parentKey.isEmpty() ? nullptr : d->_nodes.value(parentKey);
    if (!parentKey.isEmpty() && !d->_isExpander(parentNode))
        return false;

    const auto node = d->_createNode(NavigationBarType::Expander, key, title, icon);
    if (parentNode)
        parentNode->addChild(node);
    else
        d->_view->addTopLevelItem(node);

    d->_nodes.insert(key, node);
    return true;
}

bool NavigationBar::removeNode(const QString &key) {
    Q_D(NavigationBar);
    const auto node = d->_nodes.value(key);
    if (!node)
        return false;

    QList nodes{node};
    for (qsizetype index = 0; index < nodes.size(); ++index) {
        const auto current = nodes.at(index);
        for (int childIndex = 0; childIndex < current->childCount(); ++childIndex)
            nodes.append(current->child(childIndex));
    }

    for (auto current : nodes) {
        const auto currentKey = current->data(0, NavigationBarType::KeyRole).toString();
        d->_nodes.remove(currentKey);

        auto page = d->_pages.take(currentKey);
        if (!page)
            continue;

        d->_stackedWidget->removeWidget(page);
        page->deleteLater();
    }

    delete node;
    return true;
}

bool NavigationBar::setCurrentKey(const QString &key) {
    Q_D(NavigationBar);
    const auto node = d->_nodes.value(key);
    if (!node || !d->_pages.contains(key))
        return false;

    for (auto parentNode = node->parent(); parentNode; parentNode = parentNode->parent())
        parentNode->setExpanded(true);

    d->_view->setCurrentItem(node);
    d->_view->scrollToItem(node, QAbstractItemView::EnsureVisible);
    return true;
}

QString NavigationBar::currentKey() const {
    Q_D(const NavigationBar);
    const auto node = d->_view->currentItem();
    if (!node)
        return {};

    const auto key = node->data(0, NavigationBarType::KeyRole).toString();
    return d->_pages.contains(key) ? key : QString();
}

void NavigationBar::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QStyleOption option;
    option.initFrom(this);

    QStylePainter painter(this);
    painter.drawPrimitive(QStyle::PE_Widget, option);
}

void NavigationBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(NavigationBar);
    setThemeMode(mode);
    update();
    d->_view->viewport()->update();
}

TOMEER_NAMESPACE_END