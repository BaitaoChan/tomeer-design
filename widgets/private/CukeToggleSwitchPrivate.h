#ifndef CUKETOGGLESWITCHPRIVATE_H
#define CUKETOGGLESWITCHPRIVATE_H
#include <QRectF>
#include <QColor>

#include "CukeProperty.h"
#include "CukeType.h"

class QIcon;
class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN()
class ToggleSwitch;
class ToggleSwitchPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ToggleSwitch)
    CUKE_Q_PROPERTY_DECL(QColor, KnobColor)
    CUKE_Q_PROPERTY_DECL(qreal, KnobDiameter)
    CUKE_Q_PROPERTY_DECL(qreal, KnobCenterY)
    CUKE_Q_PROPERTY_DECL(qreal, KnobCenterX)
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
CUKE_NAMESPACE_END


#endif // CUKETOGGLESWITCHPRIVATE_H