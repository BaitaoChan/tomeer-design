#ifndef CUKETHEME_H
#define CUKETHEME_H
#include <QColor>
#include "CukeDef.h"
#include "CukeProperty.h"

#define pTheme CukeTheme::instance()
#define pThemeColor(Mode, Color) pTheme->getThemeColor(Mode, CukeThemeType::Color)

CUKE_BEGIN_NAMESPACE(widget)
class CukeThemePrivate;
class CUKE_EXPORT CukeTheme : public QObject {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeTheme)
private:
    explicit CukeTheme(QObject *parent = nullptr);
    ~CukeTheme() override;

public:
    static CukeTheme* instance();

    void setThemeMode(CukeThemeType::ThemeMode Mode);
    CukeThemeType::ThemeMode getThemeMode() const;

    void addThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color, QColor newColor);
    const QColor& getThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color);
signals:
    void themeModeChanged(CukeThemeType::ThemeMode Mode);

private:
    void initThemeColor();
};
CUKE_END_NAMESPACE(widget)

#endif // CUKETHEME_H
