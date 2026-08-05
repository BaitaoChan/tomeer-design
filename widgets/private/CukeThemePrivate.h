#ifndef CUKETHEMEPRIVATE_H
#define CUKETHEMEPRIVATE_H
#include <QMap>
#include <QColor>
#include "CukeType.h"
#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN()
class Theme;
class ThemePrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Theme)
    CUKE_Q_PROPERTY_DECL(qreal, ColorFactor)

public:
    explicit ThemePrivate(Theme *q);
    ~ThemePrivate() override;

private:
    ThemeType::ThemeMode _themeMode = ThemeType::Dark;
    QMap<ThemeType::ThemeColor, QColor> _lightThemeColorList;
    QMap<ThemeType::ThemeColor, QColor> _darkThemeColorList;

    QPropertyAnimation *_colorAnimation = nullptr;
};
CUKE_NAMESPACE_END

#endif // CUKETHEMEPRIVATE_H