#include <QWidget>

#include "CukeHub.h"
#include "CukeHubPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeHub::CukeHub(QObject *child)
    : d_ptr(new CukeHubPrivate(this)) {
    d_ptr->_child = child;
    setThemeMode(cTheme->getThemeMode());
    QObject::connect(cTheme, &CukeTheme::themeModeChanged, child, [this](CukeThemeType::ThemeMode mode) {
        this->onThemeChanged(mode);
    });
}

CukeHub::~CukeHub() = default;

void CukeHub::setThemeMode(CukeThemeType::ThemeMode pThemeMode) {
    if (d_ptr->_pThemeMode != pThemeMode) {
        d_ptr->_pThemeMode = pThemeMode;
    }
}
CukeThemeType::ThemeMode CukeHub::getThemeMode() const {
    return d_ptr->_pThemeMode;
}

void CukeHub::addElem(const QString &name, void *child) const {
    d_ptr->_children.insert(name, child);
}

void *CukeHub::findElem(const QString &name) const {
    return d_ptr->_children.value(name);
}

QList<void *> CukeHub::findElems() const {
    return d_ptr->_children.values();
}

bool CukeHub::hasElem(const QString &name) const {
    return d_ptr->_children.contains(name);
}

void CukeHub::onThemeChanged(CukeThemeType::ThemeMode mode) {
    setThemeMode(mode);
    if (const auto widget = qobject_cast<QWidget *>(d_ptr->_child)) {
        widget->update();
    }
}

CUKE_NAMESPACE_END(pub)