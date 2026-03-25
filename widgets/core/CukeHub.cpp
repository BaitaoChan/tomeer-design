#include <QWidget>

#include "CukeHub.h"
#include "CukeContextPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeHub::CukeHub(QObject *child)
    : d_ptr(new CukeContextPrivate(this)) {
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

void CukeHub::onThemeChanged(CukeThemeType::ThemeMode mode) {
    setThemeMode(mode);
    if (const auto widget = qobject_cast<QWidget *>(d_ptr->_child)) {
        widget->update();
    }
}

CUKE_NAMESPACE_END(pub)