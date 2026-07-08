#ifndef CUKEOBJECTMAPPRIVATE_H
#define CUKEOBJECTMAPPRIVATE_H
#include <QHash>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ObjectMap;
class ObjectMapPrivate {
    CUKE_DECLARE_QPTR(ObjectMap)
public:
    explicit ObjectMapPrivate(ObjectMap *q);
    ~ObjectMapPrivate();

private:
    QObject *_child = nullptr;

    QHash<int, void *> _children;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEOBJECTMAPPRIVATE_H
