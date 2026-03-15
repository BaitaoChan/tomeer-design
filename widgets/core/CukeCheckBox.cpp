#include "CukeCheckBox.h"
#include "CukeCheckBoxPrivate.h"
#include <QPainter>
#include <QStyleOptionButton>
CUKE_NAMESPACE_BEGIN(widget)
CUKE_Q_PROPERTY_IMPL(CukeCheckBox, qreal, CheckProgress)
CukeCheckBox::CukeCheckBox(const QString &text, QWidget *parent)
    : CukeContextMixin(parent),
    d_ptr(new CukeCheckBoxPrivate(this)) {
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumHeight(24);

    setText(text);
    // Animation
    d_ptr->_checkAnim = new QVariantAnimation(this);
    d_ptr->_checkAnim->setDuration(120);
    d_ptr->_checkAnim->setEasingCurve(QEasingCurve::OutCubic);

    connect(d_ptr->_checkAnim, &QVariantAnimation::valueChanged, this, [this](const QVariant &v) {
        setCheckProgress(v.toReal());
        update();
    });

    connect(this, &QCheckBox::toggled, this, [this](bool on) {
        d_ptr->_checkAnim->stop();
        d_ptr->_checkAnim->setStartValue(_pCheckProgress);
        d_ptr->_checkAnim->setEndValue(on ? 1.0 : 0.0);
        d_ptr->_checkAnim->start();
    });

    _pCheckProgress = isChecked() ? 1.0 : 0.0;
}

CukeCheckBox::~CukeCheckBox() = default;

void CukeCheckBox::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    const bool enabled = isEnabled();
    const bool hovered = underMouse();

    const int h = height();

    // 尺寸比例
    const int boxSize = qRound(h * 0.55);
    const int spacing = qRound(h * 0.25);
    const int radius = qRound(boxSize * 0.22);
    const int penW = qMax(1, qRound(boxSize * 0.12));
    const int leftPadding = qRound(h * 0.15);

    const int y = (h - boxSize) / 2;
    QRect boxRect(leftPadding, y, boxSize, boxSize);

    QRect textRect(
        boxRect.right() + spacing,
        0,
        width() - boxRect.right() - spacing,
        h
    );

    // 颜色
    const QColor bgColor =
            enabled
                ? (hovered
                       ? pThemeColor(_themeMode, DefaultAlpha)
                       : pThemeColor(_themeMode, DefaultAlpha))
                : pThemeColor(_themeMode, Disable);

    const QColor checkBgColor = pThemeColor(_themeMode, CheckAlpha);
    const QColor borderColor = enabled
                                   ? pThemeColor(_themeMode, Border)
                                   : pThemeColor(_themeMode, Disable);
    const QColor textColor = enabled
                                 ? pThemeColor(_themeMode, Text)
                                 : pThemeColor(_themeMode, TextDisable);

    // 背景
    const QColor finalBg =
        isChecked() ? checkBgColor : bgColor;

    p.setPen(Qt::NoPen);
    p.setBrush(finalBg);
    p.drawRoundedRect(boxRect, radius, radius);

    // 边框
    p.setPen(QPen(borderColor, 1));
    p.setBrush(Qt::NoBrush);
    p.drawRoundedRect(boxRect.adjusted(0, 0, -1, -1), radius, radius);

    // 勾选动画
    if (_pCheckProgress > 0.0) {
        p.setPen(QPen(pThemeColor(_themeMode, Text), penW, Qt::SolidLine, Qt::RoundCap));

        QPointF p1(boxRect.left() + boxSize * 0.25,
                   boxRect.top() + boxSize * 0.55);
        QPointF p2(boxRect.left() + boxSize * 0.45,
                   boxRect.top() + boxSize * 0.75);
        QPointF p3(boxRect.left() + boxSize * 0.75,
                   boxRect.top() + boxSize * 0.30);

        // 分段插值
        if (_pCheckProgress < 0.5) {
            qreal t = _pCheckProgress / 0.5;
            p.drawLine(p1, p1 + (p2 - p1) * t);
        } else {
            p.drawLine(p1, p2);
            qreal t = (_pCheckProgress - 0.5) / 0.5;
            p.drawLine(p2, p2 + (p3 - p2) * t);
        }
    }

    // 文本
    p.setPen(textColor);
    p.setFont(font());
    p.drawText(textRect, Qt::AlignVCenter | Qt::AlignLeft, text());
}

CUKE_NAMESPACE_END(widget)