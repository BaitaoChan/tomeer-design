#include <QWidget>

#include "CukeScope.h"
#include "CukeHubPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeScope::CukeScope(QObject *child)
    : d_ptr(new CukeHubPrivate(this)) {
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

void CukeScope::addElem(const QString &name, void *child) const {
    if (name.isEmpty()) {
        qCritical() << "[CukeScope] addElem failed: name is empty";
        return;
    }
    if (!child) {
        qCritical() << "[CukeScope] addElem failed:" << name << "child pointer is nullptr";
        return;
    }
    if (d_ptr->_children.contains(name)) {
        qWarning() << "[CukeScope] addElem warning:" << name << "already exists, it will be overwritten";
    }
    d_ptr->_children.insert(name, child);
}

void *CukeScope::findElem(const QString &name) const {
    if (name.isEmpty()) {
        qCritical() << "[CukeScope] findElem failed: name is empty";
        return nullptr;
    }
    if (!d_ptr->_children.contains(name)) {
        qWarning() << "[CukeScope] findElem warning:" << name << "not found";
        return nullptr;
    }
    return d_ptr->_children.value(name);
}

QList<void *> CukeScope::findElems() const {
    if (d_ptr->_children.isEmpty()) {
        qWarning() << "[CukeScope] findElems warning:" << "no elements registered";
    }
    return d_ptr->_children.values();
}

bool CukeScope::hasElem(const QString &name) const {
    if (name.isEmpty()) {
        qCritical() << "[CukeScope] hasElem failed: name is empty";
        return false;
    }
    return d_ptr->_children.contains(name);
}

void CukeScope::onThemeChanged(CukeThemeType::ThemeMode mode) {
    setThemeMode(mode);
    if (const auto widget = qobject_cast<QWidget *>(d_ptr->_child)) {
        widget->update();
    }
}

CUKE_NAMESPACE_END(pub)