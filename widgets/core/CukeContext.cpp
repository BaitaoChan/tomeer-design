#include <QWidget>

#include "CukeContext.h"
#include "CukeContextPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CukeContext::CukeContext(QObject *child)
    : d_ptr(new CukeContextPrivate(this)) {
    d_ptr->_child = child;
    setThemeMode(cTheme->getThemeMode());
    QObject::connect(cTheme, &CukeTheme::themeModeChanged, child, this->onThemeChanged);
}

CukeContext::~CukeContext() = default;

void CukeContext::onThemeChanged(CukeThemeType::ThemeMode mode) {
    setThemeMode(mode);
    if (const auto widget = qobject_cast<QWidget *>(d_ptr->_child)) {
        widget->update();
    }
}

CUKE_NAMESPACE_END(pub)