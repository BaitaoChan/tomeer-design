#include <QBrush>
#include <QPainter>
#include <QMouseEvent>
#include <QPropertyAnimation>

#include "navigation_bar_view_private.h"
#include "navigation_bar_view.h"
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

    d->_indicatorAnim = new QVariantAnimation(this);
    d->_indicatorAnim->setStartValue(0.0);
    d->_indicatorAnim->setEndValue(1.0);
    d->_indicatorAnim->setDuration(340);

    connect(d->_rotateAnim, &QPropertyAnimation::valueChanged, viewport(), QOverload<>::of(&QWidget::update));
    connect(d->_rotateAnim, &QPropertyAnimation::finished, this, [this, d] {
        d->_togglingIndex = QModelIndex();
        viewport()->update();
    });
    connect(d->_indicatorAnim, &QVariantAnimation::valueChanged,viewport(), QOverload<>::of(&QWidget::update));
    connect(d->_indicatorAnim, &QVariantAnimation::finished, this, [this, d] {
        d->_previousIndex = QModelIndex();
        d->_currentIndex = QModelIndex();
        viewport()->update();
    });
    connect(this, &QTreeWidget::expanded, d, &NavigationBarViewPrivate::onExpanded);
    connect(this, &QTreeWidget::collapsed, d, &NavigationBarViewPrivate::onCollapsed);
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

void NavigationBarView::currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    Q_D(NavigationBarView);
    QTreeWidget::currentChanged(current, previous);

    d->_indicatorAnim->stop();
    d->_previousIndex = previous;
    d->_currentIndex = current;
    d->setDownward(visualRect(current).center().y() > visualRect(previous).center().y());
    d->_indicatorAnim->start();
}

void NavigationBarView::paintEvent(QPaintEvent *event) {
    Q_D(NavigationBarView);
    QTreeWidget::paintEvent(event);

    qreal _radius = 1.5;
    
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(TOMEER_THEME->getThemeColor(ThemeType::CheckAlpha));

    // 正常绘制
    if (d->_indicatorAnim->state() != QAbstractAnimation::Running) {
        painter.drawRoundedRect(d->_indicatorRect(currentIndex()), _radius, _radius);
        return;
    }

    const int _time = d->_indicatorAnim->currentTime();
    qreal progress = 1.0;
    // 动画绘制
    if (_time < 220) {
        if (_time < 120)
            progress = QEasingCurve(QEasingCurve::InCurve).valueForProgress(_time / 120.0);
        const QRectF indicatorRect = d->_indicatorRect(d->_previousIndex);
        const QRectF borderRect = visualRect(d->_previousIndex);
        QRectF _pRect = d->_indicatorRect(d->_previousIndex);
        // 拉伸方向
        if (d->getDownward())
            _pRect.setBottom(indicatorRect.bottom() + (borderRect.bottom() - indicatorRect.bottom()) * progress);
        else
            _pRect.setTop(indicatorRect.top() + (borderRect.top() - indicatorRect.top()) * progress);
        painter.drawRoundedRect(_pRect, _radius, _radius);
        return;
    }
    progress = QEasingCurve(QEasingCurve::InQuart).valueForProgress((_time - 220) / 120.0);
    const QRectF indicatorRect = d->_indicatorRect(d->_currentIndex);
    const QRectF borderRect = visualRect(d->_currentIndex);

    QRectF _cRect = d->_indicatorRect(d->_currentIndex);

    if (d->getDownward())
        _cRect.setTop(borderRect.top() + (indicatorRect.top() - borderRect.top()) * progress);
    else
        _cRect.setBottom(borderRect.bottom() + (indicatorRect.bottom() - borderRect.bottom()) * progress);
    painter.drawRoundedRect(_cRect, _radius, _radius);
}

TOMEER_NAMESPACE_END