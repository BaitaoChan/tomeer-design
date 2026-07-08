#include "CukeCheckBox.h"
#include "CukeCheckBoxPrivate.h"
#include <QPainter>
#include <QStyleOptionButton>
CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CheckBox, qreal, CheckProgress)
CUKE_Q_PROPERTY_IMPL(CheckBox, ThemeType::ThemeMode, ThemeMode)
CheckBox::CheckBox(const QString &text, QWidget *parent)
    : QCheckBox(parent),
      d_ptr(new CheckBoxPrivate(this)) {
    Q_D(CheckBox);
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

    connect(this, &QCheckBox::toggled, d, &CheckBoxPrivate::onToggled);
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &CheckBox::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));

    _pCheckProgress = isChecked() ? 1.0 : 0.0;
}

CheckBox::~CheckBox() = default;

void CheckBox::paintEvent(QPaintEvent *event) {
    Q_D(CheckBox);
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
                       ? CUKE_THEME->getThemeColor(ThemeType::DefaultAlpha)
                       : CUKE_THEME->getThemeColor(ThemeType::DefaultAlpha))
                : CUKE_THEME->getThemeColor(ThemeType::Disable);

    const QColor checkBgColor = CUKE_THEME->getThemeColor(ThemeType::CheckAlpha);
    const QColor borderColor = enabled
                                   ? CUKE_THEME->getThemeColor(ThemeType::Border)
                                   : CUKE_THEME->getThemeColor(ThemeType::Disable);
    const QColor textColor = enabled
                                 ? CUKE_THEME->getThemeColor(ThemeType::Text)
                                 : CUKE_THEME->getThemeColor(ThemeType::TextDisable);

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
        p.setPen(QPen(CUKE_THEME->getThemeColor(ThemeType::Text), penW, Qt::SolidLine, Qt::RoundCap));

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

void CheckBox::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(CheckBox);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)