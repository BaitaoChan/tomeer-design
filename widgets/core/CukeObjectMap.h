#ifndef CUKEOBJECTMAP_H
#define CUKEOBJECTMAP_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeObjectMapPrivate;
class CUKE_EXPORT CukeObjectMap {
    CUKE_DECLARE_DPTR(CukeObjectMap);
public:
    explicit CukeObjectMap(QObject *child);
    virtual ~CukeObjectMap();

    void add(int key, void *child) const;
    void *object(int key) const;
    QList<void *> objects() const;
    bool contains(int key) const;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEOBJECTMAP_H