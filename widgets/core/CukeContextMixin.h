#ifndef CONTEXTMIXIN_H
#define CONTEXTMIXIN_H
#include <QObject>
#include <QWidget>
#include <QStyle>

#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
template<class T>
class CukeContextMixin : public T {
public:
    template<typename... Args>
    explicit CukeContextMixin(Args &&... args)
        : T(std::forward<Args>(args)...) {
        _themeMode = cTheme->getThemeMode();
        QObject::connect(cTheme, &CukeTheme::themeModeChanged, this, &CukeContextMixin::onThemeChanged);
    }

protected:
    virtual void onThemeChanged(const CukeThemeType::ThemeMode mode) {
        _themeMode = mode;
        if constexpr (std::is_base_of_v<QWidget, T>) {
            this->update();
        }
    }

    CukeThemeType::ThemeMode _themeMode;
};
CUKE_NAMESPACE_END(pub)

#endif // CONTEXTMIXIN_H
