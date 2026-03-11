#ifndef CUKETHEMEPRIVATE_H
#define CUKETHEMEPRIVATE_H
#include <QMap>
#include <QColor>
#include "CukeDef.h"
#include "CukeProperty.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeTheme;
class CukeThemePrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeTheme)

public:
    explicit CukeThemePrivate(CukeTheme *q);

    ~CukeThemePrivate() override;

private:
    CukeThemeType::ThemeMode _themeMode = CukeThemeType::Dark;
    QMap<CukeThemeType::ThemeColor, QColor> _lightThemeColorList;
    QMap<CukeThemeType::ThemeColor, QColor> _darkThemeColorList;
};
CUKE_END_NAMESPACE(widget)

#endif // CUKETHEMEPRIVATE_H
