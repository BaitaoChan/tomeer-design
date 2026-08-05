#include "CukeThemePrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_PROPERTY_IMPL(ThemePrivate, qreal, ColorFactor)
ThemePrivate::ThemePrivate(Theme *q)
    : QObject(q),
      q_ptr(q) {
}

ThemePrivate::~ThemePrivate() = default;

CUKE_NAMESPACE_END