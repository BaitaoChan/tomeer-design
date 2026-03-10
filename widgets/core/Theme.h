#ifndef THEME_H
#define THEME_H
#include <QColor>
#include "Def.h"
#include "Property.h"

#define pTheme Theme::instance()
#define pThemeColor(Mode, Color) pTheme->getThemeColor(Mode, ThemeType::Color)

CUKE_BEGIN_NAMESPACE(widget)
class ThemePrivate;
class CUKE_EXPORT Theme : public QObject {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Theme)
private:
    explicit Theme(QObject *parent = nullptr);
    ~Theme() override;

public:
    static Theme* instance();

    void setThemeMode(ThemeType::Mode Mode);
    ThemeType::Mode getThemeMode() const;

    void addThemeColor(ThemeType::Mode Mode, ThemeType::Color Color, QColor newColor);
    const QColor& getThemeColor(ThemeType::Mode Mode, ThemeType::Color Color);
signals:
    void themeModeChanged(ThemeType::Mode Mode);

private:
    void initThemeColor();
};
CUKE_END_NAMESPACE(widget)

#endif // THEME_H
