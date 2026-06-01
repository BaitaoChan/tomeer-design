#include "CukeCheckBox.h"
#include "CukeCheckBoxPrivate.h"
#include <QPainter>
#include <QStyleOptionButton>
CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeCheckBox, qreal, CheckProgress)
CUKE_Q_PROPERTY_IMPL(CukeCheckBox, CukeThemeType::ThemeMode, ThemeMode)
CukeCheckBox::CukeCheckBox(const QString &text, QWidget *parent)
    : QCheckBox(parent),
      d_ptr(new CukeCheckBoxPrivate(this)) {
    Q_D(CukeCheckBox);
    setCursor(Qt::PointingHandCursor);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    setMinimumHeight(24);

    setText(text);
    // Animation
    d->_checkAnim = new QVariantAnimation(this);
    d->_checkAnim->setDuration(120);
    d->_checkAnim->setEasingCurve(QEasingCurve::OutCubic);

    connect(d->_checkAnim, &QVariantAnimation::valueChanged, this, [this](const QVariant &v) {
        setCheckProgress(v.toReal());
        update();
    });

    connect(this, &QCheckBox::toggled, d, &CukeCheckBoxPrivate::onToggled);
    connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeCheckBox::onThemeChanged);

    _pCheckProgress = isChecked() ? 1.0 : 0.0;
}

CukeCheckBox::~CukeCheckBox() = default;

void CukeCheckBox::paintEvent(QPaintEvent *event) {
    Q_D(CukeCheckBox);
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
                       ? cTheme->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha)
                       : cTheme->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha))
                : cTheme->getThemeColor(getThemeMode(), CukeThemeType::Disable);

    const QColor checkBgColor = cTheme->getThemeColor(getThemeMode(), CukeThemeType::CheckAlpha);
    const QColor borderColor = enabled
                                   ? cTheme->getThemeColor(getThemeMode(), CukeThemeType::Border)
                                   : cTheme->getThemeColor(getThemeMode(), CukeThemeType::Disable);
    const QColor textColor = enabled
                                 ? cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text)
                                 : cTheme->getThemeColor(getThemeMode(), CukeThemeType::TextDisable);

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
        p.setPen(QPen(cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text), penW, Qt::SolidLine, Qt::RoundCap));

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

void CukeCheckBox::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeCheckBox);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)