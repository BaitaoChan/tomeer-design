#include <QPropertyAnimation>
#include <QPainter>

#include "CukeLineEdit.h"
#include "CukeLineEditStyle.h"
#include "CukeLineEditPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(LineEdit, QColor, BorderColor)
CUKE_Q_PROPERTY_IMPL(LineEdit, int, LineHalfWidth)
CUKE_Q_PROPERTY_IMPL(LineEdit, int, BorderRadius)
CUKE_Q_PROPERTY_IMPL(LineEdit, ThemeType::ThemeMode, ThemeMode)
LineEdit::LineEdit(QWidget *parent)
    : QLineEdit(parent),
      _pBorderRadius(6),
      d_ptr(new LineEditPrivate(this)) {
    Q_D(LineEdit);
    setStyle(new LineEditStyle(style()));
    setFixedHeight(30);
    setAttribute(Qt::WA_TranslucentBackground);

    // 边框颜色动画
    d->_borderAnim = new QPropertyAnimation(this, "_pBorderColor", this);
    d->_borderAnim->setDuration(250);
    d->_borderAnim->setEasingCurve(QEasingCurve::InOutSine);

    d->_lineAnim = new QPropertyAnimation(this, QByteArrayLiteral("_pLineHalfWidth"), this);
    d->_lineAnim->setDuration(250);
    d->_lineAnim->setEasingCurve(QEasingCurve::InOutCubic);

    setStyleSheet("QLineEdit { border: none; padding-left: 8px; background: transparent; }");

    connect(d->_borderAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d->_lineAnim, &QPropertyAnimation::finished, d, &LineEditPrivate::onLineAnimFinished);
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &LineEdit::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

LineEdit::~LineEdit() = default;

void LineEdit::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(LineEdit);
    setThemeMode(mode);
    // 设置文字颜色
    QPalette pal = palette();
    pal.setColor(QPalette::Text, CUKE_THEME->getThemeColor(ThemeType::Text));
    setPalette(pal);

    if (!d->_isFocused) {
        _pBorderColor = CUKE_THEME->getThemeColor(ThemeType::BorderAlpha);
    }
    update();
}

void LineEdit::focusInEvent(QFocusEvent *event) {
    Q_D(LineEdit);
    d->_isFocused = true;
    d->_hasFocusVisible = true;
    d->_borderAnim->stop();
    d->_borderAnim->setStartValue(CUKE_THEME->getThemeColor(ThemeType::BorderAlpha));
    d->_borderAnim->setEndValue(CUKE_THEME->getThemeColor(ThemeType::FocusBorder));
    d->_borderAnim->start();

    d->_lineAnim->stop();
    d->_lineAnim->setStartValue(0);
    d->_lineAnim->setEndValue(width() / 2);
    d->_lineAnim->start();

    QLineEdit::focusInEvent(event);
}

void LineEdit::focusOutEvent(QFocusEvent *event) {
    Q_D(LineEdit);
    d->_isFocused = false;
    d->_borderAnim->stop();
    d->_borderAnim->setStartValue(CUKE_THEME->getThemeColor(ThemeType::FocusBorder));
    d->_borderAnim->setEndValue(CUKE_THEME->getThemeColor(ThemeType::BorderAlpha));
    d->_borderAnim->start();

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
        d->_lineAnim->setEndValue(width() / 2);
        d->_lineAnim->start();
    } else {
        _pLineHalfWidth = 0;
        update();
    }
}


void LineEdit::paintEvent(QPaintEvent *event) {
    Q_D(LineEdit);
    QLineEdit::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(ThemeType::DefaultAlpha));
    QRect r = rect().adjusted(1, 1, -1, -1);
    p.drawRoundedRect(r, _pBorderRadius, _pBorderRadius);

    // 绘制边框
    QPen pen(CUKE_THEME->getThemeColor(ThemeType::BorderAlpha), 1);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(r, _pBorderRadius, _pBorderRadius);

    // 绘制焦点边框
    pen.setColor(_pBorderColor);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(r, _pBorderRadius, _pBorderRadius);

    // 绘制底部横线
    if (d->_hasFocusVisible) {
        pen.setWidth(3);
        p.setPen(pen);
        int y = height() - 1;
        int centerX = width() / 2;
        int threshold = 10;
        if (_pLineHalfWidth <= threshold) {
            int adjustedOffset = qMax(0, 8 - (threshold - _pLineHalfWidth));
            p.drawLine(centerX - _pLineHalfWidth + adjustedOffset, y,
                       centerX + _pLineHalfWidth - adjustedOffset, y);
        } else {
            p.drawLine(centerX - _pLineHalfWidth + 8, y,
                       centerX + _pLineHalfWidth - 8, y);
        }
    }
}

CUKE_NAMESPACE_END(pub)