#include "CukeSliderPrivate.h"
#include "CukeSlider.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeSliderPrivate::CukeSliderPrivate(CukeSlider *q)
    : QObject(q),
      q_ptr(q) {
}

CukeSliderPrivate::~CukeSliderPrivate() = default;

CUKE_NAMESPACE_END(pub)