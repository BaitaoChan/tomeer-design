#ifndef CUKEHUBPRIVATE_H
#define CUKEHUBPRIVATE_H
#include <QHash>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeScope;
class CukeHubPrivate {
    CUKE_DECLARE_QPTR(CukeScope)
public:
    explicit CukeHubPrivate(CukeScope *q);
    ~CukeHubPrivate();

private:
    QObject *_child = nullptr;
    CukeThemeType::ThemeMode _pThemeMode = CukeThemeType::Light;

    QHash<QString, void *> _children;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEHUBPRIVATE_H
