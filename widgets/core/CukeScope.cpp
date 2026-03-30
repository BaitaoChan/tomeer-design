#include <QWidget>

#include "CukeScope.h"
#include "CukeScopePrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeScope::CukeScope(QObject *child)
    : d_ptr(new CukeScopePrivate(this)) {
    d_ptr->_child = child;
    setThemeMode(cTheme->getThemeMode());
    QObject::connect(cTheme, &CukeTheme::themeModeChanged, child, [this](CukeThemeType::ThemeMode mode) {
        this->onThemeChanged(mode);
    });
}

CukeScope::~CukeScope() = default;

void CukeScope::setThemeMode(CukeThemeType::ThemeMode pThemeMode) {
    if (d_ptr->_pThemeMode != pThemeMode) {
        d_ptr->_pThemeMode = pThemeMode;
    }
}
CukeThemeType::ThemeMode CukeScope::getThemeMode() const {
    return d_ptr->_pThemeMode;
}

void CukeScope::addElem(const int key, void *child) const {
    if (!child) {
        qCritical() << "[CukeScope] addElem failed:" << "key =" << key << ", child pointer is nullptr";
        return;
    }
    if (d_ptr->_children.contains(key)) {
        qWarning() << "[CukeScope] addElem warning:" << "key =" << key << "already exists, it will be overwritten";
    }
    d_ptr->_children.insert(key, child);
}

void *CukeScope::findElem(const int key) const {
    if (!d_ptr->_children.contains(key)) {
        qWarning() << "[CukeScope] findElem warning:" << "key =" << key << "not found";
        return nullptr;
    }
    return d_ptr->_children.value(key);
}

QList<void *> CukeScope::findElems() const {
    if (d_ptr->_children.isEmpty()) {
        qWarning() << "[CukeScope] findElems warning:" << "no elements registered";
    }
    return d_ptr->_children.values();
}

bool CukeScope::hasElem(const int key) const {
    return d_ptr->_children.contains(key);
}

void CukeScope::onThemeChanged(CukeThemeType::ThemeMode mode) {
    setThemeMode(mode);
    if (const auto widget = qobject_cast<QWidget *>(d_ptr->_child)) {
        widget->update();
    }
}

CUKE_NAMESPACE_END(pub)