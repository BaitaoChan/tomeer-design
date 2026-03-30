#ifndef CUKESCOPEPRIVATE_H
#define CUKESCOPEPRIVATE_H
#include <QHash>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeScope;
class CukeScopePrivate {
    CUKE_DECLARE_QPTR(CukeScope)
public:
    explicit CukeScopePrivate(CukeScope *q);
    ~CukeScopePrivate();

private:
    QObject *_child = nullptr;
    CukeThemeType::ThemeMode _pThemeMode = CukeThemeType::Light;

    QHash<int, void *> _children;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCOPEPRIVATE_H
