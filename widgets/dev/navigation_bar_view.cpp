#include "navigation_bar_view.h"

#include <QBrush>
#include <QFontMetrics>
#include <QHelpEvent>
#include <QMouseEvent>
#include <QPalette>
#include <QPropertyAnimation>

#include "scroll_bar.h"
#include "tool_tip.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(NavigationBarView, qreal, RotateAngle)

NavigationBarView::NavigationBarView(QWidget *parent)
    : QTreeWidget(parent) {
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

    _rotateAnim = new QPropertyAnimation(this, "_pRotateAngle", this);
    _rotateAnim->setDuration(300);
    _rotateAnim->setEasingCurve(QEasingCurve::InOutSine);

    connect(_rotateAnim, &QPropertyAnimation::valueChanged, viewport(), QOverload<>::of(&QWidget::update));
    connect(_rotateAnim, &QPropertyAnimation::finished, this, [this] {
        _animatedIndex = QModelIndex();
        viewport()->update();
    });
    connect(this, &QTreeWidget::expanded, this, &NavigationBarView::onExpanded);
    connect(this, &QTreeWidget::collapsed, this, &NavigationBarView::onCollapsed);
}

NavigationBarView::~NavigationBarView() = default;

bool NavigationBarView::isIndexPressed(const QModelIndex &index) const {
    return _pressedIndex == index;
}

bool NavigationBarView::isIndexAnimated(const QModelIndex &index) const {
    return _animatedIndex == index;
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
    _pressedIndex = indexAt(event->position().toPoint());
    viewport()->update();

    if (event->button() == Qt::LeftButton) {
        if (_pressedIndex.isValid()) {
            const auto nodeType = static_cast<NavigationBarType::NodeType>(_pressedIndex.data(NavigationBarType::NodeTypeRole).toInt());
            if (nodeType == NavigationBarType::Expander) {
                event->accept();
                return;
            }
        }
    }
    QTreeWidget::mousePressEvent(event);
}

void NavigationBarView::mouseReleaseEvent(QMouseEvent *event) {
    const QModelIndex releasedIndex = indexAt(event->position().toPoint());
    bool isExpander = false;
    if (releasedIndex.isValid()) {
        if (releasedIndex == _pressedIndex) {
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

    _pressedIndex = QModelIndex();
    viewport()->update();
}

void NavigationBarView::onExpanded(const QModelIndex &index) {
    qreal startAngle = 0.0;
    if (_animatedIndex == index) {
        if (_rotateAnim->state() == QAbstractAnimation::Running)
            startAngle = getRotateAngle();
    }

    _rotateAnim->stop();
    _animatedIndex = index;
    setRotateAngle(startAngle);
    _rotateAnim->setStartValue(startAngle);
    _rotateAnim->setEndValue(180.0);
    _rotateAnim->start();
}

void NavigationBarView::onCollapsed(const QModelIndex &index) {
    qreal startAngle = 180.0;
    if (_animatedIndex == index) {
        if (_rotateAnim->state() == QAbstractAnimation::Running)
            startAngle = getRotateAngle();
    }

    _rotateAnim->stop();
    _animatedIndex = index;
    setRotateAngle(startAngle);
    _rotateAnim->setStartValue(startAngle);
    _rotateAnim->setEndValue(0.0);
    _rotateAnim->start();
}

TOMEER_NAMESPACE_END