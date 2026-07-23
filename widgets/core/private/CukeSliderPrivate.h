#ifndef CUKESLIDERPRIVATE_H
#define CUKESLIDERPRIVATE_H
#include <QPoint>
#include <QRect>

#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(pub)
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
CUKE_NAMESPACE_END(pub)


#endif // CUKESLIDERPRIVATE_H