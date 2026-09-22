#include <QPropertyAnimation>
#include <QPainter>

#include "line_edit.h"
#include "line_edit_style.h"
#include "line_edit_private.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(LineEdit, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(LineEdit, int, LineHalfWidth)
TOMEER_Q_PROPERTY_IMPL(LineEdit, ThemeType::ThemeMode, ThemeMode)
LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent),
      _pBorderRadius(6),
      d_ptr(new LineEditPrivate(this)) {
    Q_D(LineEdit);
    setStyle(new LineEditStyle(style()));
    setFixedHeight(30);
    setAttribute(Qt::WA_TranslucentBackground);

    d->_lineAnim = new QPropertyAnimation(this, "_pLineHalfWidth", this);
    d->_lineAnim->setDuration(300);
    d->_lineAnim->setEasingCurve(QEasingCurve::InOutSine);

    setTextMargins(8, 0, 0, 0);

    connect(d->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &LineEdit::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

LineEdit::~LineEdit() = default;

void LineEdit::onThemeChanged(ThemeType::ThemeMode mode) {
    setThemeMode(mode);
    style()->polish(this);
    update();
}

void LineEdit::focusInEvent(QFocusEvent *event) {
    Q_D(LineEdit);
    d->_isFocused = true;

    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(0);
    d->_lineAnim->setEndValue((rect().right() - rect().left() - 8) / 2.0);
    d->_lineAnim->start();

    QLineEdit::focusInEvent(event);
}

void LineEdit::focusOutEvent(QFocusEvent *event) {
    Q_D(LineEdit);
    d->_isFocused = false;

    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(_pLineHalfWidth);
    d->_lineAnim->setEndValue(0);
    d->_lineAnim->start();

    QLineEdit::focusOutEvent(event);
}

void LineEdit::resizeEvent(QResizeEvent *event) {
    Q_D(LineEdit);
    QLineEdit::resizeEvent(event);

    if (d->_isFocused) {
        d->_lineAnim->stop();
        d->_lineAnim->setStartValue(_pLineHalfWidth);
        d->_lineAnim->setEndValue((rect().right() - rect().left() - 8) / 2.0);
        d->_lineAnim->start();
    } else {
        _pLineHalfWidth = 0;
        update();
    }
}


void LineEdit::paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);

    QPalette pal = palette();
    pal.setColor(QPalette::Text, TOMEER_THEME->getThemeColor(ThemeType::Text));
    setPalette(pal);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    // 绘制底部横线
    p.setPen(Qt::NoPen);
    p.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Pattern));
    p.drawRoundedRect(QRectF(rect().left() + 4,
                             rect().bottom() - 3,
                             rect().right() - rect().left() - 8,
                             2),
                      2,
                      2);

    // 焦点指示
    p.setBrush(TOMEER_THEME->getThemeColor(ThemeType::Check));
    p.drawRoundedRect(QRectF(rect().left() + 4 + (rect().right() - rect().left() - 8) / 2.0 - _pLineHalfWidth,
                             rect().bottom() - 3,
                             _pLineHalfWidth * 2,
                             3),
                      2,
                      2);
}

TOMEER_NAMESPACE_END
