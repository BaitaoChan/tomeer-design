#ifndef CUKETHEMEPRIVATE_H
#define CUKETHEMEPRIVATE_H
#include <QMap>
#include <QColor>
#include "CukeType.h"
#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(pub)
class CukeTheme;
class CukeThemePrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeTheme)
    CUKE_Q_PROPERTY_DECL(qreal, ColorFactor)

public:
    explicit CukeThemePrivate(CukeTheme *q);
    ~CukeThemePrivate() override;

private:
    CukeThemeType::ThemeMode _themeMode = CukeThemeType::Dark;
    QMap<CukeThemeType::ThemeColor, QColor> _lightThemeColorList;
    QMap<CukeThemeType::ThemeColor, QColor> _darkThemeColorList;

    QPropertyAnimation *_colorAnimation = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETHEMEPRIVATE_H
