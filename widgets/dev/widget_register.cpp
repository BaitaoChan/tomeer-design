#include <QWidget>

#include "widget_register.h"
#include "widget_register_private.h"

TOMEER_NAMESPACE_BEGIN()
WidgetRegister::WidgetRegister(QObject *child)
    : d_ptr(new WidgetRegisterPrivate(this)) {
    d_ptr->_child = child;
}

WidgetRegister::~WidgetRegister() = default;

void WidgetRegister::add(const int key, void *child) const {
    if (!child) {
        return;
    }
    if (d_ptr->_children.contains(key)) {
    }
    d_ptr->_children.insert(key, child);
}

void *WidgetRegister::object(const int key) const {
    if (!d_ptr->_children.contains(key)) {
        return nullptr;
    }
    return d_ptr->_children.value(key);
}

QList<void *> WidgetRegister::objects() const {
    if (d_ptr->_children.isEmpty()) {
    }
    return d_ptr->_children.values();
}

bool WidgetRegister::contains(const int key) const {
    return d_ptr->_children.contains(key);
}

TOMEER_NAMESPACE_END