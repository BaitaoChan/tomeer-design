#include "CukeSliderPrivate.h"
#include "CukeSlider.h"

CUKE_NAMESPACE_BEGIN(pub)
SliderPrivate::SliderPrivate(Slider *q)
    : QObject(q),
      q_ptr(q) {
}

SliderPrivate::~SliderPrivate() = default;

CUKE_NAMESPACE_END(pub)