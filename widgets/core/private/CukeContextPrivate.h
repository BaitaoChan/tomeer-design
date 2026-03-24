#ifndef CUKECONTEXTPRIVATE_H
#define CUKECONTEXTPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeContext;
class CukeContextPrivate {
    CUKE_DECLARE_QPTR(CukeContext)
public:
    explicit CukeContextPrivate(CukeContext *q);
    ~CukeContextPrivate();

private:
    QObject *_child = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECONTEXTPRIVATE_H
