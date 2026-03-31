#include "CukeToggleSwitchPrivate.h"
#include "CukeToggleSwitch.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitchPrivate, QColor, KnobColor)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitchPrivate, qreal, KnobDiameter)
CUKE_Q_PROPERTY_IMPL(CukeToggleSwitchPrivate, qreal, KnobCenterY)
CukeToggleSwitchPrivate::CukeToggleSwitchPrivate(CukeToggleSwitch *q)
    : QObject(q),
      q_ptr(q) {
}

CukeToggleSwitchPrivate::~CukeToggleSwitchPrivate() = default;

void CukeToggleSwitchPrivate::setKnobCenterX(qreal knobX) {
    if (!qFuzzyCompare(_pKnobCenterX + 1.0, knobX + 1.0)) {
        // qFuzzyCompare 对 qreal 比较
        _pKnobCenterX = knobX;
    }
}

qreal CukeToggleSwitchPrivate::getKnobCenterX() const {
    return _pKnobCenterX;
}

CUKE_NAMESPACE_END(pub)