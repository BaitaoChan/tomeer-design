#ifndef THEME_PRIVATE_H
#define THEME_PRIVATE_H
#include <QMap>
#include <QColor>
#include "type.h"
#include "property.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class Theme;
class ThemePrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(Theme)
    TOMEER_Q_PROPERTY_DECL(qreal, ColorFactor)

public:
    explicit ThemePrivate(Theme *q);
    ~ThemePrivate() override;

private:
    ThemeType::ThemeMode _themeMode = ThemeType::Light;
    QMap<ThemeType::ThemeColor, QColor> _lightThemeColorList;
    QMap<ThemeType::ThemeColor, QColor> _darkThemeColorList;

    QPropertyAnimation *_colorAnimation = nullptr;
};
TOMEER_NAMESPACE_END

#endif // THEME_PRIVATE_H