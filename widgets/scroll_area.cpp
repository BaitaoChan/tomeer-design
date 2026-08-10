#include <QPainter>
#include <QPropertyAnimation>
#include <QWheelEvent>

#include "scroll_area.h"
#include "scroll_area_private.h"
#include "scroll_bar.h"

TOMEER_NAMESPACE_BEGIN()
    TOMEER_Q_PROPERTY_IMPL(ScrollArea, ThemeType::ThemeMode, ThemeMode)
ScrollArea::ScrollArea(QWidget *parent)
    : QScrollArea(parent),
      d_ptr(new ScrollAreaPrivate(this)) {
    Q_D(ScrollArea);
    setHorizontalScrollBar(new ScrollBar(this));
    setVerticalScrollBar(new ScrollBar(this));
    setStyleSheet("QScrollArea { border: none; background: transparent; }");
    viewport()->setStyleSheet("background: transparent;");

    d->_horScrollAnim = new QPropertyAnimation(horizontalScrollBar(), "value", this);
    d->_horScrollAnim->setDuration(160);
    d->_horScrollAnim->setEasingCurve(QEasingCurve::OutCubic);
    d->_verScrollAnim = new QPropertyAnimation(verticalScrollBar(), "value", this);
    d->_verScrollAnim->setDuration(160);
    d->_verScrollAnim->setEasingCurve(QEasingCurve::OutCubic);

    connect(verticalScrollBar(), &QScrollBar::sliderPressed, d->_verScrollAnim, &QPropertyAnimation::stop);
    connect(horizontalScrollBar(), &QScrollBar::sliderPressed, d->_horScrollAnim, &QPropertyAnimation::stop);
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, QOverload<>::of(&QWidget::update));
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ScrollArea::~ScrollArea() = default;

void ScrollArea::paintEvent(QPaintEvent *event) {
    QScrollArea::paintEvent(event);
}

void ScrollArea::wheelEvent(QWheelEvent *event) {
    Q_D(ScrollArea);
    const int verValue = verticalScrollBar()->value();
    const int horValue = horizontalScrollBar()->value();

    QScrollArea::wheelEvent(event);

    const int _verValue = verticalScrollBar()->value();
    const int _horValue = horizontalScrollBar()->value();
    if (_verValue != verValue) {
        int _value = verValue;
        if (d->_verScrollAnim->state() == QAbstractAnimation::Running)
            _value = d->_verScrollAnim->endValue().toInt();

        d->_verScrollAnim->stop();
        verticalScrollBar()->setValue(verValue);
        _value = qBound(verticalScrollBar()->minimum(), _value + _verValue - verValue, verticalScrollBar()->maximum());
        d->_verScrollAnim->setStartValue(verValue);
        d->_verScrollAnim->setEndValue(_value);
        d->_verScrollAnim->start();
    }
    if (_horValue != horValue) {
        int _value = horValue;
        if (d->_horScrollAnim->state() == QAbstractAnimation::Running)
            _value = d->_horScrollAnim->endValue().toInt();

        d->_horScrollAnim->stop();
        horizontalScrollBar()->setValue(horValue);
        _value = qBound(horizontalScrollBar()->minimum(), _value + _horValue - horValue,
                        horizontalScrollBar()->maximum());
        d->_horScrollAnim->setStartValue(horValue);
        d->_horScrollAnim->setEndValue(_value);
        d->_horScrollAnim->start();
    }
}

void ScrollArea::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ScrollArea);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END