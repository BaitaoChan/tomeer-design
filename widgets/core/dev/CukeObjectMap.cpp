#include <QWidget>

#include "CukeObjectMap.h"
#include "CukeObjectMapPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
ObjectMap::ObjectMap(QObject *child)
    : d_ptr(new ObjectMapPrivate(this)) {
    d_ptr->_child = child;
}

ObjectMap::~ObjectMap() = default;

void ObjectMap::add(const int key, void *child) const {
    if (!child) {
        return;
    }
    if (d_ptr->_children.contains(key)) {
    }
    d_ptr->_children.insert(key, child);
}

void *ObjectMap::object(const int key) const {
    if (!d_ptr->_children.contains(key)) {
        return nullptr;
    }
    return d_ptr->_children.value(key);
}

QList<void *> ObjectMap::objects() const {
    if (d_ptr->_children.isEmpty()) {
    }
    return d_ptr->_children.values();
}

bool ObjectMap::contains(const int key) const {
    return d_ptr->_children.contains(key);
}

CUKE_NAMESPACE_END(pub)