#ifndef NAVIGATION_BAR_PRIVATE_H
#define NAVIGATION_BAR_PRIVATE_H
#include <QHash>
#include <QString>

#include "property.h"
#include "type.h"

class QWidget;
class QStackedWidget;
class QTreeWidgetItem;
TOMEER_NAMESPACE_BEGIN()
class NavigationBar;
class NavigationBarView;
class NavigationBarPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(NavigationBar)
public:
    explicit NavigationBarPrivate(NavigationBar *q);
    ~NavigationBarPrivate() override;

    Q_SLOT void onCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    bool _isExpander(const QTreeWidgetItem *node) const;
    QTreeWidgetItem *_createNode(NavigationBarType::NodeType type, const QString &key, const QString &title, IconType::Icon icon) const;

    int _expandedWidth = 220;
    int _compactWidth = 42;
    int _minimalWidth = 0;
    int _expandedThreshold = 850;
    int _compactThreshold = 550;

    NavigationBarView *_view = nullptr;
    QStackedWidget *_stackedWidget = nullptr;
    QHash<QString, QTreeWidgetItem *> _nodes;
    QHash<QString, QWidget *> _pages;
};
TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_PRIVATE_H
