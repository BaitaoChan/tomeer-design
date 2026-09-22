#ifndef TOGGLE_SWITCH_PRIVATE_H
#define TOGGLE_SWITCH_PRIVATE_H
#include <QRectF>
#include <QColor>

#include "property.h"
#include "type.h"

class QIcon;
class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class ToggleSwitch;
class ToggleSwitchPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(ToggleSwitch)
    TOMEER_Q_PROPERTY_DECL(QColor, KnobColor)
    TOMEER_Q_PROPERTY_DECL(qreal, KnobDiameter)
    TOMEER_Q_PROPERTY_DECL(qreal, KnobCenterY)
    TOMEER_Q_PROPERTY_DECL(qreal, KnobCenterX)
public:
    explicit ToggleSwitchPrivate(ToggleSwitch *q);
    ~ToggleSwitchPrivate() override;

private:
    bool _isToggled = false;
    bool _isPressed = false;

    QIcon *_icon = nullptr;

    qreal knobDiameterHover = 0, knobDiameterPress = 0, knobDiameter = 0;

    qreal knobCenterXL = 0, knobCenterXR = 0;

    QColor knobColor = QColor();
    QColor onBgColor = QColor();
    QColor offBgColor = QColor();
    QColor borderColor = QColor();

    QPropertyAnimation *_bgAnimation = nullptr;
    QPropertyAnimation *_knobColorAnimation = nullptr;
    QPropertyAnimation *_knobDiameterAnimation = nullptr;
    QPropertyAnimation *_moveAnimation = nullptr;

    QColor *_bgColorFrom = nullptr;
    QColor *_bgColorTo = nullptr;

};
TOMEER_NAMESPACE_END


#endif // TOGGLE_SWITCH_PRIVATE_H
