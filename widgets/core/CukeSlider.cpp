#include "CukeSlider.h"
#include "CukeSliderPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CUKE_Q_PROPERTY_IMPL(CukeSlider, qreal, HandleDiameter)

CukeSlider::CukeSlider(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeSliderPrivate(this)) {
    setOrientation(Qt::Horizontal);
    setContentsMargins(4, 0, 4, 0);

    d_ptr->_handleDiameterAnimation = new QPropertyAnimation(this, "_pHandleDiameter", this);
    d_ptr->_handleDiameterAnimation->setDuration(200);
    d_ptr->_handleDiameterAnimation->setEasingCurve(QEasingCurve::InOutSine);

    connect(d_ptr->_handleDiameterAnimation, &QPropertyAnimation::valueChanged, this,
            QOverload<>::of(&QWidget::update));
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
    setMouseTracking(false);
    d_ptr->_handleDiameterAnimation->stop();
    d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
    d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameter);
    d_ptr->_handleDiameterAnimation->start();
    QSlider::leaveEvent(event);
}

void CukeSlider::mouseMoveEvent(QMouseEvent *event) {
    if (d_ptr->_isPressed) {
        // 拖动过程中保持 Press 大小
        if (_pHandleDiameter != d_ptr->handleDiameterPress) {
            d_ptr->_handleDiameterAnimation->stop();
            d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameterPress);
            d_ptr->_handleDiameterAnimation->start();
        }
    } else {
        // 没有按下时，正常 hover 判断
        if (d_ptr->_handleRect.contains(event->pos())) {
            d_ptr->_handleDiameterAnimation->stop();
            d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameterHover);
            d_ptr->_handleDiameterAnimation->start();
        } else {
            d_ptr->_handleDiameterAnimation->stop();
            d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameter);
            d_ptr->_handleDiameterAnimation->start();
        }
    }
    QSlider::mouseMoveEvent(event);
}

void CukeSlider::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && d_ptr->_handleRect.contains(event->pos())) {
        d_ptr->_isPressed = true;
        d_ptr->_handleDiameterAnimation->stop();
        d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
        d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameterPress);
        d_ptr->_handleDiameterAnimation->start();
    }
    QSlider::mousePressEvent(event);
}

void CukeSlider::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        d_ptr->_isPressed = false;
        // 松开后，如果还在 handle 上，回到 hover，否则回到默认
        if (d_ptr->_handleRect.contains(event->pos())) {
            d_ptr->_handleDiameterAnimation->stop();
            d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameterHover);
            d_ptr->_handleDiameterAnimation->start();
        } else {
            d_ptr->_handleDiameterAnimation->stop();
            d_ptr->_handleDiameterAnimation->setStartValue(_pHandleDiameter);
            d_ptr->_handleDiameterAnimation->setEndValue(d_ptr->handleDiameter);
            d_ptr->_handleDiameterAnimation->start();
        }
    }
    QSlider::mouseReleaseEvent(event);
}

void CukeSlider::resizeEvent(QResizeEvent *event) {
    QSlider::resizeEvent(event);

    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect handleRect = style()->subControlRect(QStyle::CC_Slider, &opt,
                                               QStyle::SC_SliderHandle, this);

    if (d_ptr->handleDiameter == 0) {
        d_ptr->handleDiameter = handleRect.width() / 4;
        d_ptr->handleDiameterHover = d_ptr->handleDiameter * 1.2;
        d_ptr->handleDiameterPress = d_ptr->handleDiameter * 0.8;
        if (_pHandleDiameter == 0)
            _pHandleDiameter = d_ptr->handleDiameter;
    }
}

void CukeSlider::paintEvent(QPaintEvent *event) {
    QStyleOptionSlider opt;
    initStyleOption(&opt);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    d_ptr->_handleRect = style()->subControlRect(QStyle::CC_Slider, &opt,
                                                 QStyle::SC_SliderHandle, this);
    d_ptr->_handleCenter = d_ptr->_handleRect.center();

    // 滑轨
    int grooveHeight = 5; // 滑轨厚度
    QRectF grooveRect(10, d_ptr->_handleCenter.y() - grooveHeight / 2.0, width() - 20, grooveHeight);
    p.setPen(Qt::NoPen);
    p.setBrush(pThemeColor(_themeMode, CukeThemeType::DefaultAlpha));
    p.drawRoundedRect(grooveRect, 3, 3);

    // 已滑过部分
    QRectF subRect = grooveRect;
    subRect.setRight(d_ptr->_handleCenter.x());
    p.setBrush(pThemeColor(_themeMode, CukeThemeType::CheckAlpha));
    p.drawRoundedRect(subRect, 3, 3);

    // 滑块外圆
    p.setPen(Qt::NoPen);
    p.setBrush(pThemeColor(_themeMode, CukeThemeType::SliderHandleBorder));
    p.drawEllipse(d_ptr->_handleCenter, d_ptr->_handleRect.width() / 2.5, d_ptr->_handleRect.width() / 2.5);

    // 滑块内圆
    p.setPen(Qt::NoPen);
    p.setBrush(pThemeColor(_themeMode, CukeThemeType::Check));
    p.drawEllipse(d_ptr->_handleCenter, _pHandleDiameter, _pHandleDiameter);
}

CUKE_END_NAMESPACE(widget)