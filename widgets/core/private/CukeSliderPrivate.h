#ifndef CUKESLIDERPRIVATE_H
#define CUKESLIDERPRIVATE_H
#include <QPoint>
#include <QRect>

#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_BEGIN_NAMESPACE(widget)
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
CUKE_END_NAMESPACE(widget)


#endif // CUKESLIDERPRIVATE_H
