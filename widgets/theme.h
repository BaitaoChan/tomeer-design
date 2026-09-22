#ifndef THEME_H
#define THEME_H
#include <QColor>
#include "type.h"
#include "property.h"

#define TOMEER_THEME Theme::instance()

TOMEER_NAMESPACE_BEGIN()
class ThemePrivate;
class WIDGETS_EXPORT Theme : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(Theme)
    TOMEER_Q_SINGLETON_DECL(Theme)
    TOMEER_Q_PROPERTY_DECL(bool, FollowSystem)
private:
    explicit Theme(QObject *parent = nullptr);
    ~Theme() override;

public:
    void setThemeMode(ThemeType::ThemeMode mode);
    ThemeType::ThemeMode getThemeMode();

    void addThemeColor(ThemeType::ThemeMode mode, ThemeType::ThemeColor color, QColor newColor);

    QColor getThemeColor(ThemeType::ThemeColor color);
    QColor getThemeColor(ThemeType::ThemeMode mode, ThemeType::ThemeColor color);
signals:
    void themeModeChanged(ThemeType::ThemeMode mode);
    void themeColorChanged();
private slots:
    void onColorSchemeChanged(Qt::ColorScheme colorScheme);
private:
    void initThemeColor();
};
TOMEER_NAMESPACE_END

#endif // THEME_H
