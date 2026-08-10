#include "toggle_switch_private.h"
#include "toggle_switch.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ToggleSwitchPrivate, QColor, KnobColor)
TOMEER_Q_PROPERTY_IMPL(ToggleSwitchPrivate, qreal, KnobDiameter)
TOMEER_Q_PROPERTY_IMPL(ToggleSwitchPrivate, qreal, KnobCenterY)
ToggleSwitchPrivate::ToggleSwitchPrivate(ToggleSwitch *q)
    : QObject(q),
      q_ptr(q) {
}

ToggleSwitchPrivate::~ToggleSwitchPrivate() = default;

void ToggleSwitchPrivate::setKnobCenterX(qreal knobX) {
    if (!qFuzzyCompare(_pKnobCenterX + 1.0, knobX + 1.0)) {
        // qFuzzyCompare 对 qreal 比较
        _pKnobCenterX = knobX;
    }
}

qreal ToggleSwitchPrivate::getKnobCenterX() const {
    return _pKnobCenterX;
}

TOMEER_NAMESPACE_END