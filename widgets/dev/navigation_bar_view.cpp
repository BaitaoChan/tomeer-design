#include "navigation_bar_view.h"

#include <QKeyEvent>
#include <QMouseEvent>

TOMEER_NAMESPACE_BEGIN()

NavigationBarView::NavigationBarView(QWidget *parent)
    : QTreeWidget(parent) {
    setHeaderHidden(true);
    setColumnCount(1);
    setRootIsDecorated(true);
    setAnimated(true);
    setMouseTracking(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    setAutoFillBackground(false);
    viewport()->setAutoFillBackground(false);
}

NavigationBarView::~NavigationBarView() = default;

void NavigationBarView::mousePressEvent(QMouseEvent *event) {
    QTreeWidget::mousePressEvent(event);
}

void NavigationBarView::keyPressEvent(QKeyEvent *event) {
    QTreeWidget::keyPressEvent(event);
}

TOMEER_NAMESPACE_END