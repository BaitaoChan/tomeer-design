#ifndef CUKEOBJECTMAPPRIVATE_H
#define CUKEOBJECTMAPPRIVATE_H
#include <QHash>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeObjectMap;
class CukeObjectMapPrivate {
    CUKE_DECLARE_QPTR(CukeObjectMap)
public:
    explicit CukeObjectMapPrivate(CukeObjectMap *q);
    ~CukeObjectMapPrivate();

private:
    QObject *_child = nullptr;

    QHash<int, void *> _children;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEOBJECTMAPPRIVATE_H
