#include <QHelpEvent>

#include "CukeSlider.h"
#include "CukeSliderPrivate.h"
#include "CukeToolTip.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(Slider, qreal, HandleDiameter)
CUKE_Q_PROPERTY_IMPL(Slider, ThemeType::ThemeMode, ThemeMode)
Slider::Slider(QWidget *parent)
    : QSlider(parent),
      d_ptr(new SliderPrivate(this)) {
    Q_D(Slider);
    setOrientation(Qt::Horizontal);
    setContentsMargins(4, 0, 4, 0);

    d->_handleDiameterAnimation = new QPropertyAnimation(this, "_pHandleDiameter", this);
    d->_handleDiameterAnimation->setDuration(200);
    d->_handleDiameterAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_handleDiameterAnimation, &QPropertyAnimation::valueChanged, this,
            QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &Slider::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

Slider::Slider(Qt::Orientation orientation, QWidget *parent)
    : Slider(parent) {
    setOrientation(orientation);
}

Slider::~Slider() = default;

bool Slider::event(QEvent *event) {
    if (event->type() == QEvent::ToolTip) {
        const auto helpEvent = dynamic_cast<QHelpEvent *>(event);
        if (!toolTip().isEmpty())
            ToolTip::showText(helpEvent->globalPos(), toolTip(), this);
        else {
            ToolTip::hideText();
            event->ignore();
        }
        return true;
    }
    if (event->type() == QEvent::Leave || event->type() == QEvent::Hide)
        ToolTip::hideText();
    return QSlider::event(event);
}

void Slider::enterEvent(QEnterEvent *event) {
    setMouseTracking(true);
    QSlider::enterEvent(event);
}

void Slider::leaveEvent(QEvent *event) {
    Q_D(Slider);
    setMouseTracking(false);
    d->_handleDiameterAnimation->stop();
    d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
    d->_handleDiameterAnimation->setEndValue(d->handleDiameter);
    d->_handleDiameterAnimation->start();
    QSlider::leaveEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event) {
    Q_D(Slider);
    if (d->_isPressed) {
        // 拖动过程中保持 Press 大小
        if (_pHandleDiameter != d->handleDiameterPress) {
            d->_handleDiameterAnimation->stop();
            d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d->_handleDiameterAnimation->setEndValue(d->handleDiameterPress);
            d->_handleDiameterAnimation->start();
        }
    } else {
        // 没有按下时，正常 hover 判断
        if (d->_handleRect.contains(event->pos())) {
            d->_handleDiameterAnimation->stop();
            d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d->_handleDiameterAnimation->setEndValue(d->handleDiameterHover);
            d->_handleDiameterAnimation->start();
        } else {
            d->_handleDiameterAnimation->stop();
            d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d->_handleDiameterAnimation->setEndValue(d->handleDiameter);
            d->_handleDiameterAnimation->start();
        }
    }
    QSlider::mouseMoveEvent(event);

    // 鼠标移动更新 ToolTip 的位置
    if (d->_isPressed)
        ToolTip::showText(event->globalPosition().toPoint(), QString::number(sliderPosition()), this);
}

void Slider::mousePressEvent(QMouseEvent *event) {
    Q_D(Slider);
    if (event->button() == Qt::LeftButton && d->_handleRect.contains(event->pos())) {
        d->_isPressed = true;
        d->_handleDiameterAnimation->stop();
        d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
        d->_handleDiameterAnimation->setEndValue(d->handleDiameterPress);
        d->_handleDiameterAnimation->start();
    }
    QSlider::mousePressEvent(event);

    if (d->_isPressed)
        ToolTip::showText(event->globalPosition().toPoint(), QString::number(sliderPosition()), this);
}

void Slider::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(Slider);
    if (event->button() == Qt::LeftButton) {
        d->_isPressed = false;
        ToolTip::hideText();
        // 松开后，如果还在 handle 上，回到 hover，否则回到默认
        if (d->_handleRect.contains(event->pos())) {
            d->_handleDiameterAnimation->stop();
            d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d->_handleDiameterAnimation->setEndValue(d->handleDiameterHover);
            d->_handleDiameterAnimation->start();
        } else {
            d->_handleDiameterAnimation->stop();
            d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d->_handleDiameterAnimation->setEndValue(d->handleDiameter);
            d->_handleDiameterAnimation->start();
        }
    }
    QSlider::mouseReleaseEvent(event);
}

void Slider::resizeEvent(QResizeEvent *event) {
    Q_D(Slider);
    QSlider::resizeEvent(event);

    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

    if (d->handleDiameter == 0) {
        d->handleDiameter = handleRect.width() / 4;
        d->handleDiameterHover = d->handleDiameter * 1.2;
        d->handleDiameterPress = d->handleDiameter * 0.8;
        if (_pHandleDiameter == 0)
            _pHandleDiameter = d->handleDiameter;
    }
}

void Slider::paintEvent(QPaintEvent *event) {
    Q_D(Slider);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    d->_handleRect = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    d->_handleCenter = d->_handleRect.center();

    // 滑轨
    int grooveHeight = 5; // 滑轨厚度
    const qreal margin = (d->_handleRect.width() - 1) / 2.0;
    QRectF grooveRect(margin, d->_handleCenter.y() - grooveHeight / 2.0, width() - 1 - margin * 2, grooveHeight);
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(ThemeType::DefaultAlpha));
    p.drawRoundedRect(grooveRect, 3, 3);

    // 已滑过部分
    QRectF subRect = grooveRect;
    subRect.setRight(d->_handleCenter.x());
    p.setBrush(CUKE_THEME->getThemeColor(ThemeType::CheckAlpha));
    p.drawRoundedRect(subRect, 3, 3);

    // 滑块外圆
    p.setBrush(CUKE_THEME->getThemeColor(ThemeType::SliderHandleBorder));
    p.drawEllipse(d->_handleCenter, d->_handleRect.width() / 2.5, d->_handleRect.width() / 2.5);

    // 滑块内圆
    p.setBrush(CUKE_THEME->getThemeColor(ThemeType::Check));
    p.drawEllipse(d->_handleCenter, _pHandleDiameter, _pHandleDiameter);
}

void Slider::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(Slider);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END