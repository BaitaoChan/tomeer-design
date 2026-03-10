#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>
#include <QStyleOptionSlider>
#include <QPainter>
#include <QPropertyAnimation>
#include <QMouseEvent>

#include "Property.h"
#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class SliderPrivate;
class CUKE_EXPORT Slider : public ContextMixin<QSlider> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Slider)
    CUKE_Q_PROPERTY_DECL(qreal, HandleDiameter)
public:
    explicit Slider(QWidget *parent = nullptr);
    explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~Slider() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};
CUKE_END_NAMESPACE(widget)

#endif // SLIDER_H
