#ifndef CUKETOGGLESWITCHPRIVATE_H
#define CUKETOGGLESWITCHPRIVATE_H
#include <QRectF>
#include <QColor>

#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_BEGIN_NAMESPACE(widget)
class CukeToggleSwitch;
class CukeToggleSwitchPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeToggleSwitch)
public:
    explicit CukeToggleSwitchPrivate(CukeToggleSwitch *q);
    ~CukeToggleSwitchPrivate() override;

private:
    bool _isToggled = false;
    bool _isPressed = false;

    qreal knobDiameterHover = 0, knobDiameterPress = 0, knobDiameter = 0;

    QRectF _knobRect = QRectF();

    qreal knobCenterXL = 0, knobCenterXR = 0;

    QColor knobColor = QColor();
    QColor onBgColor = QColor();
    QColor offBgColor = QColor();
    QColor borderColor = QColor();

    QPropertyAnimation* _bgAnimation = nullptr;
    QPropertyAnimation* _knobColorAnimation = nullptr;
    QPropertyAnimation* _knobDiameterAnimation = nullptr;
    QPropertyAnimation* _moveAnimation = nullptr;

};
CUKE_END_NAMESPACE(widget)


#endif // CUKETOGGLESWITCHPRIVATE_H
