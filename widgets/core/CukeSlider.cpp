#include "CukeSlider.h"
#include "CukeSliderPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeSlider, qreal, HandleDiameter)
CUKE_Q_PROPERTY_IMPL(CukeSlider, CukeThemeType::ThemeMode, ThemeMode)
CukeSlider::CukeSlider(QWidget *parent)
    : QSlider(parent),
      d_ptr(new CukeSliderPrivate(this)) {
    Q_D(CukeSlider);
    setOrientation(Qt::Horizontal);
    setContentsMargins(4, 0, 4, 0);

    d->_handleDiameterAnimation = new QPropertyAnimation(this, "_pHandleDiameter", this);
    d->_handleDiameterAnimation->setDuration(200);
    d->_handleDiameterAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(d->_handleDiameterAnimation, &QPropertyAnimation::valueChanged, this,
            QOverload<>::of(&QWidget::update));
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeSlider::onThemeChanged);
}

CukeSlider::CukeSlider(Qt::Orientation orientation, QWidget *parent)
    : CukeSlider(parent) {
    setOrientation(orientation);
}

CukeSlider::~CukeSlider() = default;

void CukeSlider::enterEvent(QEnterEvent *event) {
    setMouseTracking(true);
    QSlider::enterEvent(event);
}

void CukeSlider::leaveEvent(QEvent *event) {
    Q_D(CukeSlider);
    setMouseTracking(false);
    d->_handleDiameterAnimation->stop();
    d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
    d->_handleDiameterAnimation->setEndValue(d->handleDiameter);
    d->_handleDiameterAnimation->start();
    QSlider::leaveEvent(event);
}

void CukeSlider::mouseMoveEvent(QMouseEvent *event) {
    Q_D(CukeSlider);
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
}

void CukeSlider::mousePressEvent(QMouseEvent *event) {
    Q_D(CukeSlider);
    if (event->button() == Qt::LeftButton && d->_handleRect.contains(event->pos())) {
        d->_isPressed = true;
        d->_handleDiameterAnimation->stop();
        d->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
        d->_handleDiameterAnimation->setEndValue(d->handleDiameterPress);
        d->_handleDiameterAnimation->start();
    }
    QSlider::mousePressEvent(event);
}

void CukeSlider::mouseReleaseEvent(QMouseEvent *event) {
    Q_D(CukeSlider);
    if (event->button() == Qt::LeftButton) {
        d->_isPressed = false;
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

void CukeSlider::resizeEvent(QResizeEvent *event) {
    Q_D(CukeSlider);
    QSlider::resizeEvent(event);

    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt,
                                               QStyle::SC_SliderHandle, this);

    if (d->handleDiameter == 0) {
        d->handleDiameter = handleRect.width() / 4;
        d->handleDiameterHover = d->handleDiameter * 1.2;
        d->handleDiameterPress = d->handleDiameter * 0.8;
        if (_pHandleDiameter == 0)
            _pHandleDiameter = d->handleDiameter;
    }
}

void CukeSlider::paintEvent(QPaintEvent *event) {
    Q_D(CukeSlider);
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    d->_handleRect = style()->subControlRect(QStyle::CC_Slider, &opt,
                                                 QStyle::SC_SliderHandle, this);
    d->_handleCenter = d->_handleRect.center();

    // 滑轨
    int grooveHeight = 5; // 滑轨厚度
    QRectF grooveRect(10, d->_handleCenter.y() - grooveHeight / 2.0, width() - 20, grooveHeight);
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::DefaultAlpha));
    p.drawRoundedRect(grooveRect, 3, 3);

    // 已滑过部分
    QRectF subRect = grooveRect;
    subRect.setRight(d->_handleCenter.x());
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::CheckAlpha));
    p.drawRoundedRect(subRect, 3, 3);

    // 滑块外圆
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::SliderHandleBorder));
    p.drawEllipse(d->_handleCenter, d->_handleRect.width() / 2.5, d->_handleRect.width() / 2.5);

    // 滑块内圆
    p.setPen(Qt::NoPen);
    p.setBrush(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Check));
    p.drawEllipse(d->_handleCenter, _pHandleDiameter, _pHandleDiameter);
}

void CukeSlider::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeSlider);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)