#include "slider_private.h"
#include "slider.h"

TOMEER_NAMESPACE_BEGIN()
SliderPrivate::SliderPrivate(Slider *q)
    : QObject(q),
      q_ptr(q) {
}

SliderPrivate::~SliderPrivate() = default;

TOMEER_NAMESPACE_END