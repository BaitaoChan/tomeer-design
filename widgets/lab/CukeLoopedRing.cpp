#include "CukeLoopedRing.h"
#include "CukeLoopedRingPrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(lab)
CUKE_Q_PROPERTY_IMPL(CukeLoopedRing, qreal, Angle)
CUKE_Q_PROPERTY_IMPL(CukeLoopedRing, CukeThemeType::ThemeMode, ThemeMode)
CukeLoopedRing::CukeLoopedRing(QWidget *parent)
    : QWidget(parent),
      d_ptr(new CukeLoopedRingPrivate(this)) {
    Q_D(CukeLoopedRing);
    setFixedSize(200, 200);

    d->_animation = new QPropertyAnimation(this, "_pAngle");
    d->_animation->setTargetObject(this);
    d->_animation->setDuration(6000);
    d->_animation->setLoopCount(-1);
    d->_animation->setEasingCurve(QEasingCurve::Linear);

    d->_font = new QFont();
    d->_font->setPointSize(12);
    d->_font->setWeight(QFont::Weight::Normal);

    connect(d->_animation, &QPropertyAnimation::valueChanged, this, QOverload<>::of(&QWidget::update));
}

CukeLoopedRing::~CukeLoopedRing() = default;

void CukeLoopedRing::setText(const QString &text) {
    Q_D(CukeLoopedRing);
    d->_text = text;
    update();
}

void CukeLoopedRing::start() {
    Q_D(CukeLoopedRing);
    d->_animation->stop();
    d->_animation->setStartValue(0);
    d->_animation->setEndValue(360);
    d->_animation->start();
}

void CukeLoopedRing::stop() {
    Q_D(CukeLoopedRing);
    d->_animation->stop();
}

void CukeLoopedRing::exec() {
    Q_D(CukeLoopedRing);
    if (d->_animation->state() == QAbstractAnimation::Stopped)
        start();
    else
        stop();
}

void CukeLoopedRing::paintEvent(QPaintEvent *event) {
    Q_D(CukeLoopedRing);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int widgetWidth = width();
    const int widgetHeight = height();

    QColor colorBright = CUKE_THEME->getThemeColor(CukeThemeType::LoopRing);
    const QColor colorMedium(colorBright.red(), colorBright.green(), colorBright.blue(), 200);
    const QColor colorDim(colorBright.red(), colorBright.green(), colorBright.blue(), 160);

    painter.translate(widgetWidth / 2, widgetHeight / 2);

    // Outer ring
    QPen penOuter(colorDim);
    penOuter.setWidth(4);
    penOuter.setCapStyle(Qt::RoundCap);
    painter.setPen(penOuter);

    const QRectF outerRingRect(-0.45 * widgetWidth, -0.45 * widgetHeight,
                               0.9 * widgetWidth, 0.9 * widgetHeight);

    static const qreal baseStartAngle = 30;
    static const qreal baseSpanAngle = 120;

    qreal angle = _pAngle;
    painter.rotate(angle);
    painter.drawArc(outerRingRect, baseStartAngle * 16, baseSpanAngle * 16);
    painter.drawArc(outerRingRect, (baseStartAngle + 180) * 16, baseSpanAngle * 16);
    painter.resetTransform();


    // Middle ring
    QPen penMiddle(colorMedium);
    penMiddle.setWidth(4);
    penMiddle.setCapStyle(Qt::RoundCap);
    painter.setPen(penMiddle);

    painter.translate(widgetWidth / 2, widgetHeight / 2);

    const QRectF middleRingRect(-0.375 * widgetWidth, -0.375 * widgetHeight,
                                0.75 * widgetWidth, 0.75 * widgetHeight);

    qreal middleAngle = _pAngle;
    if (middleAngle > 180) middleAngle -= 180;

    painter.rotate(-2 * middleAngle);
    painter.drawArc(middleRingRect, baseStartAngle * 16, baseSpanAngle * 16);
    painter.drawArc(middleRingRect, (baseStartAngle + 180) * 16, baseSpanAngle * 16);
    painter.resetTransform();


    // Inner dynamic ring
    QPen penInner(colorBright);
    penInner.setWidth(4);
    penInner.setCapStyle(Qt::RoundCap);
    painter.setPen(penInner);

    painter.translate(widgetWidth / 2, widgetHeight / 2);

    const QRectF innerRingRect(-0.3 * widgetWidth, -0.3 * widgetHeight,
                               0.6 * widgetWidth, 0.6 * widgetHeight);

    qreal innerAngle = _pAngle;
    static const qreal cycleAngle = 120;

    while (innerAngle > cycleAngle) innerAngle -= cycleAngle;
    painter.rotate(innerAngle * 90 / cycleAngle);

    qreal dynamicStart1 = 15 + (90 - 15) * (innerAngle / cycleAngle);
    qreal dynamicSpan1 = 180 - 2 * dynamicStart1;

    if (dynamicSpan1 > 0) {
        painter.drawArc(innerRingRect, dynamicStart1 * 16, dynamicSpan1 * 16);
        painter.drawArc(innerRingRect, (dynamicStart1 + 180) * 16, dynamicSpan1 * 16);
    }

    qreal dynamicStart2 = -75 * (innerAngle / cycleAngle);
    qreal dynamicSpan2 = -dynamicStart2 * 2;

    if (dynamicSpan2 > 0) {
        painter.drawArc(innerRingRect, dynamicStart2 * 16, dynamicSpan2 * 16);
        painter.drawArc(innerRingRect, (dynamicStart2 + 180) * 16, dynamicSpan2 * 16);
    }

    painter.resetTransform();


    // Draw text & glow effect
    painter.setFont(*d->_font);

    QPainterPath textClipPath;
    textClipPath.addText(
        QPointF((widgetWidth - QFontMetrics(*d->_font).horizontalAdvance(d->_text)) / 2,
            0.5 * widgetHeight + QFontMetrics(*d->_font).height() / 4),
        *d->_font,
        d->_text
    );

    painter.setClipPath(textClipPath);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(colorDim));
    painter.drawRect(rect());

    painter.translate(0, 0.5 * widgetHeight);

    const qreal pixelPerDegree = widgetWidth / 360.0;

    QRadialGradient textGlow(QPointF(_pAngle * pixelPerDegree, 0),
        QFontMetrics(*d->_font).height());
    textGlow.setColorAt(0, colorBright);
    textGlow.setColorAt(1, colorDim);

    painter.setBrush(textGlow);
    painter.drawEllipse(QPointF(_pAngle * pixelPerDegree, 0),
        QFontMetrics(*d->_font).height(),
        QFontMetrics(*d->_font).height());
}

CUKE_NAMESPACE_END(lab)