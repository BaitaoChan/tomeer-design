#ifndef CUKECONTEXTPRIVATE_H
#define CUKECONTEXTPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeHub;
class CukeContextPrivate {
    CUKE_DECLARE_QPTR(CukeHub)
public:
    explicit CukeContextPrivate(CukeHub *q);
    ~CukeContextPrivate();

private:
    QObject *_child = nullptr;
    CukeThemeType::ThemeMode _pThemeMode = CukeThemeType::Light;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECONTEXTPRIVATE_H
