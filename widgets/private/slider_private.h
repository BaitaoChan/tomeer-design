#ifndef SLIDER_PRIVATE_H
#define SLIDER_PRIVATE_H
#include <QPoint>
#include <QRect>

#include "property.h"
#include "type.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class Slider;
class SliderPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(Slider)
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
TOMEER_NAMESPACE_END


#endif // SLIDER_PRIVATE_H