#ifndef CUKESLIDERPRIVATE_H
#define CUKESLIDERPRIVATE_H
#include <QPoint>
#include <QRect>

#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(widget)
class CukeSlider;
class CukeSliderPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeSlider)
public:
    explicit CukeSliderPrivate(CukeSlider* q);
    ~CukeSliderPrivate() override;

private:
    bool _isPressed = false;

    QPointF _handleCenter = QPointF();
    QRect _handleRect = QRect();
    qreal handleDiameterHover = 0, handleDiameterPress = 0, handleDiameter = 0;

    QPropertyAnimation* _handleDiameterAnimation = nullptr;

};
CUKE_NAMESPACE_END(widget)


#endif // CUKESLIDERPRIVATE_H
