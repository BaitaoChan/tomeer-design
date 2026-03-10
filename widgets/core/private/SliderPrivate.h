#ifndef SLIDERPRIVATE_H
#define SLIDERPRIVATE_H
#include <QPoint>
#include <QRect>

#include "Property.h"

class QPropertyAnimation;
CUKE_BEGIN_NAMESPACE(widget)
class Slider;
class SliderPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Slider)
public:
    explicit SliderPrivate(Slider* q);
    ~SliderPrivate() override;

private:
    bool _isPressed = false;

    QPointF _handleCenter = QPointF();
    QRect _handleRect = QRect();
    qreal handleDiameterHover = 0, handleDiameterPress = 0, handleDiameter = 0;

    QPropertyAnimation* _handleDiameterAnimation = nullptr;

};
CUKE_END_NAMESPACE(widget)


#endif // SLIDERPRIVATE_H
