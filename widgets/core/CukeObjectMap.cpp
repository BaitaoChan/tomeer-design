#include <QWidget>

#include "CukeObjectMap.h"
#include "CukeObjectMapPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeObjectMap::CukeObjectMap(QObject *child)
    : d_ptr(new CukeObjectMapPrivate(this)) {
    d_ptr->_child = child;
}

CukeObjectMap::~CukeObjectMap() = default;

void CukeObjectMap::add(const int key, void *child) const {
    if (!child) {
        return;
    }
    if (d_ptr->_children.contains(key)) {
    }
    d_ptr->_children.insert(key, child);
}

void *CukeObjectMap::object(const int key) const {
    if (!d_ptr->_children.contains(key)) {
        return nullptr;
    }
    return d_ptr->_children.value(key);
}

QList<void *> CukeObjectMap::objects() const {
    if (d_ptr->_children.isEmpty()) {
    }
    return d_ptr->_children.values();
}

bool CukeObjectMap::contains(const int key) const {
    return d_ptr->_children.contains(key);
}

CUKE_NAMESPACE_END(pub)