#include "theme_private.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ThemePrivate, qreal, ColorFactor)
ThemePrivate::ThemePrivate(Theme *q)
    : QObject(q),
      q_ptr(q) {
}

ThemePrivate::~ThemePrivate() = default;

TOMEER_NAMESPACE_END