#ifndef CONTEXTMIXIN_H
#define CONTEXTMIXIN_H
#include <QObject>
#include <QWidget>
#include <QStyle>

#include "Theme.h"

CUKE_BEGIN_NAMESPACE(widget)
template<class T>
class ContextMixin : public T {
public:
    template<typename... Args>
    explicit ContextMixin(Args &&... args)
        : T(std::forward<Args>(args)...) {
        _themeMode = pTheme->getThemeMode();
        QObject::connect(pTheme, &Theme::themeModeChanged, this, &ContextMixin::onThemeChanged);
    }

protected:
    virtual void onThemeChanged(const ThemeType::Mode mode) {
        _themeMode = mode;
        if constexpr (std::is_base_of_v<QWidget, T>) {
            this->update();
        }
    }

    ThemeType::Mode _themeMode;
};
CUKE_END_NAMESPACE(widget)

#endif // CONTEXTMIXIN_H
