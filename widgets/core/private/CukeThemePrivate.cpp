#include "CukeThemePrivate.h"
#include "CukeCheckBox.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeThemePrivate::CukeThemePrivate(CukeTheme *q)
    : QObject(q),
      q_ptr(q) {
}

CukeThemePrivate::~CukeThemePrivate() = default;

CUKE_NAMESPACE_END(pub)