#include <QPropertyAnimation>
#include <QPainter>

#include "CukeLineEdit.h"
#include "CukeLineEditStyle.h"
#include "CukeLineEditPrivate.h"

CUKE_NAMESPACE_BEGIN(widget)
CUKE_Q_PROPERTY_IMPL(CukeLineEdit, QColor, BorderColor)
CUKE_Q_PROPERTY_IMPL(CukeLineEdit, int, LineHalfWidth)
CUKE_Q_PROPERTY_IMPL(CukeLineEdit, int, BorderRadius)

CukeLineEdit::CukeLineEdit(QWidget *parent)
    : CukeContextMixin(parent),
      _pBorderRadius(6),
      d_ptr(new CukeLineEditPrivate(this)) {
    _themeMode = pTheme->getThemeMode();

    setStyle(new CukeLineEditStyle(style()));
    setFixedHeight(30);
    setAttribute(Qt::WA_TranslucentBackground);

    // 边框颜色动画
    d_ptr->_borderAnim = new QPropertyAnimation(this, "_pBorderColor", this);
    d_ptr->_borderAnim->setDuration(250);
    d_ptr->_borderAnim->setEasingCurve(QEasingCurve::InOutSine);

    d_ptr->_lineAnim = new QPropertyAnimation(this, QByteArrayLiteral("_pLineHalfWidth"), this);
    d_ptr->_lineAnim->setDuration(250);
    d_ptr->_lineAnim->setEasingCurve(QEasingCurve::InOutCubic);

    setStyleSheet("QLineEdit { border: none; padding-left: 8px; background: transparent; }");

    connect(d_ptr->_borderAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_lineAnim, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
    connect(d_ptr->_lineAnim, &QPropertyAnimation::finished, this, [this]() {
        if (!d_ptr->_isFocused) {
            d_ptr->_hasFocusVisible = false;
            update();
        }
    });
}

CukeLineEdit::~CukeLineEdit() = default;

void CukeLineEdit::onThemeChanged(CukeThemeType::ThemeMode mode) {
    CukeContextMixin::onThemeChanged(mode);
    // 设置文字颜色
    QPalette pal = palette();
    pal.setColor(QPalette::Text, pThemeColor(_themeMode, CukeThemeType::Text));
    setPalette(pal);

    if (!d_ptr->_isFocused) {
        _pBorderColor = pThemeColor(_themeMode, BorderAlpha);
    }
    update();
}

void CukeLineEdit::focusInEvent(QFocusEvent *event) {
    d_ptr->_isFocused = true;
    d_ptr->_hasFocusVisible = true;
    d_ptr->_borderAnim->stop();
    d_ptr->_borderAnim->setStartValue(pThemeColor(_themeMode, BorderAlpha));
    d_ptr->_borderAnim->setEndValue(pThemeColor(_themeMode, FocusBorder));
    d_ptr->_borderAnim->start();

    d_ptr->_lineAnim->stop();
    d_ptr->_lineAnim->setStartValue(0);
    d_ptr->_lineAnim->setEndValue(width() / 2);
    d_ptr->_lineAnim->start();

    QLineEdit::focusInEvent(event);
}

void CukeLineEdit::focusOutEvent(QFocusEvent *event) {
    d_ptr->_isFocused = false;
    d_ptr->_borderAnim->stop();
    d_ptr->_borderAnim->setStartValue(pThemeColor(_themeMode, FocusBorder));
    d_ptr->_borderAnim->setEndValue(pThemeColor(_themeMode, BorderAlpha));
    d_ptr->_borderAnim->start();

    d_ptr->_lineAnim->stop();
    d_ptr->_lineAnim->setStartValue(_pLineHalfWidth);
    d_ptr->_lineAnim->setEndValue(0);
    d_ptr->_lineAnim->start();

    QLineEdit::focusOutEvent(event);
}

void CukeLineEdit::resizeEvent(QResizeEvent *event) {
    QLineEdit::resizeEvent(event);

    if (d_ptr->_isFocused) {
        d_ptr->_lineAnim->stop();
        d_ptr->_lineAnim->setStartValue(_pLineHalfWidth);
        d_ptr->_lineAnim->setEndValue(width() / 2);
        d_ptr->_lineAnim->start();
    } else {
        _pLineHalfWidth = 0;
        update();
    }
}


void CukeLineEdit::paintEvent(QPaintEvent *event) {
    QLineEdit::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 绘制背景
    p.setPen(Qt::NoPen);
    p.setBrush(pThemeColor(_themeMode, CukeThemeType::DefaultAlpha));
    QRect r = rect().adjusted(1, 1, -1, -1);
    p.drawRoundedRect(r, _pBorderRadius, _pBorderRadius);

    // 绘制边框
    QPen pen(pThemeColor(_themeMode, BorderAlpha), 1);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(r, _pBorderRadius, _pBorderRadius);

    // 绘制焦点边框
    pen.setColor(_pBorderColor);
    p.setPen(pen);
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(r, _pBorderRadius, _pBorderRadius);

    // 绘制底部横线
    if (d_ptr->_hasFocusVisible) {
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

CUKE_NAMESPACE_END(widget)