#ifndef CUKEOBJECTMAP_H
#define CUKEOBJECTMAP_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ObjectMapPrivate;
class CUKE_EXPORT ObjectMap {
    CUKE_DECLARE_DPTR(ObjectMap);
public:
    explicit ObjectMap(QObject *child);
    virtual ~ObjectMap();

    void add(int key, void *child) const;
    void *object(int key) const;
    QList<void *> objects() const;
    bool contains(int key) const;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEOBJECTMAP_H