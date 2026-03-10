#ifndef THEMEPRIVATE_H
#define THEMEPRIVATE_H
#include <QMap>
#include <QColor>
#include "Def.h"
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class Theme;
class ThemePrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Theme)

public:
    explicit ThemePrivate(Theme *q);

    ~ThemePrivate() override;

private:
    ThemeType::Mode _themeMode = ThemeType::Dark;
    QMap<ThemeType::Color, QColor> _lightThemeColorList;
    QMap<ThemeType::Color, QColor> _darkThemeColorList;
};
CUKE_END_NAMESPACE(widget)

#endif // THEMEPRIVATE_H
