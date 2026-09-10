#include "navigation_bar_view.h"

#include <QBrush>
#include <QFontMetrics>
#include <QHelpEvent>
#include <QMouseEvent>
#include <QPalette>
#include <QPropertyAnimation>

#include "navigation_bar_view_private.h"
#include "scroll_bar.h"
#include "tool_tip.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(NavigationBarView, qreal, RotateAngle)

NavigationBarView::NavigationBarView(QWidget *parent)
    : QTreeWidget(parent),
      d_ptr(new NavigationBarViewPrivate(this)) {
    Q_D(NavigationBarView);

    setHorizontalScrollBar(new ScrollBar(this));
    setVerticalScrollBar(new ScrollBar(this));
    setHeaderHidden(true);
    setColumnCount(1);
    setIconSize(QSize(QFontMetrics(font()).height(), QFontMetrics(font()).height()));
    setRootIsDecorated(false);
    setAnimated(true);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollMode(ScrollPerPixel);
    setFrameShape(NoFrame);

    setAutoFillBackground(false);
    viewport()->setAutoFillBackground(false);

    QPalette viewPalette = palette();
    viewPalette.setBrush(QPalette::Base, QBrush(Qt::NoBrush));
    setPalette(viewPalette);
    viewport()->setPalette(viewPalette);

    d->_rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    d->_rotateAnim->setDuration(300);
    d->_rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_rotateAnim, &QPropertyAnimation::valueChanged, viewport(), QOverload<>::of(&QWidget::update));
    connect(d->_rotateAnim, &QPropertyAnimation::finished, this, [this, d] {
        d->_togglingIndex = QModelIndex();
        viewport()->update();
    });
    connect(this, &QTreeWidget::expanded, this, &NavigationBarView::onExpanded);
    connect(this, &QTreeWidget::collapsed, this, &NavigationBarView::onCollapsed);
}

NavigationBarView::~NavigationBarView() = default;

bool NavigationBarView::isPressed(const QModelIndex &index) const {
    Q_D(const NavigationBarView);
    return d->_pressedIndex == index;
}

bool NavigationBarView::isToggling(const QModelIndex &index) const {
    Q_D(const NavigationBarView);
    return d->_togglingIndex == index;
}

bool NavigationBarView::viewportEvent(QEvent *event) {
    if (event->type() == QEvent::ToolTip) {
        const auto helpEvent = dynamic_cast<QHelpEvent *>(event);
        const auto index = indexAt(helpEvent->pos());
        const auto text = index.data(Qt::ToolTipRole).toString();
        if (!text.isEmpty())
            ToolTip::showText(helpEvent->globalPos(), text, viewport());
        else {
            ToolTip::hideText();
            event->ignore();
        }
        return true;
    }
    if (event->type() == QEvent::Leave || event->type() == QEvent::Hide)
        ToolTip::hideText();
    return QTreeWidget::viewportEvent(event);
}

void NavigationBarView::mousePressEvent(QMouseEvent *event) {
    Q_D(NavigationBarView);
    d->_pressedIndex = indexAt(event->position().toPoint());
    viewport()->update();

    if (event->button() == Qt::LeftButton) {
        if (d->_pressedIndex.isValid()) {
            const auto nodeType = static_cast<NavigationBarType::NodeType>(d->_pressedIndex.data(NavigationBarType::NodeTypeRole).toInt());
            if (nodeType == NavigationBarType::Expander) {
                event->accept();
                return;
            }
        }
    }
    QTreeWidget::mousePressEvent(event);
}

void NavigationBarView::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(NavigationBarView);
    const QModelIndex releasedIndex = indexAt(event->position().toPoint());
    bool isExpander = false;
    if (releasedIndex.isValid()) {
        if (releasedIndex == d->_pressedIndex) {
            const auto nodeType = static_cast<NavigationBarType::NodeType>(releasedIndex.data(NavigationBarType::NodeTypeRole).toInt());
            if (nodeType == NavigationBarType::Expander)
                isExpander = true;
        }
    }

    if (event->button() == Qt::LeftButton) {
        if (isExpander) {
            setExpanded(releasedIndex, !isExpanded(releasedIndex));
            event->accept();
        } else {
            QTreeWidget::mouseReleaseEvent(event);
        }
    } else {
        QTreeWidget::mouseReleaseEvent(event);
    }

    d->_pressedIndex = QModelIndex();
    viewport()->update();
}

void NavigationBarView::onExpanded(const QModelIndex &index) {
    Q_D(NavigationBarView);
    qreal startAngle = 0.0;
    if (d->_togglingIndex == index) {
        if (d->_rotateAnim->state() == QAbstractAnimation::Running)
            startAngle = getRotateAngle();
    }

    d->_rotateAnim->stop();
    d->_togglingIndex = index;
    setRotateAngle(startAngle);
    d->_rotateAnim->setStartValue(startAngle);
    d->_rotateAnim->setEndValue(180.0);
    d->_rotateAnim->start();
}

void NavigationBarView::onCollapsed(const QModelIndex &index) {
    Q_D(NavigationBarView);
    qreal startAngle = 180.0;
    if (d->_togglingIndex == index) {
        if (d->_rotateAnim->state() == QAbstractAnimation::Running)
            startAngle = getRotateAngle();
    }

    d->_rotateAnim->stop();
    d->_togglingIndex = index;
    setRotateAngle(startAngle);
    d->_rotateAnim->setStartValue(startAngle);
    d->_rotateAnim->setEndValue(0.0);
    d->_rotateAnim->start();
}

TOMEER_NAMESPACE_END