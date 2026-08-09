#ifndef CUKETHEME_H
#define CUKETHEME_H
#include <QColor>
#include "CukeType.h"
#include "CukeProperty.h"

#define CUKE_THEME Theme::instance()

CUKE_NAMESPACE_BEGIN()
class ThemePrivate;
class CUKE_EXPORT Theme : public QObject {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Theme)
    CUKE_Q_SINGLETON_DECL(Theme)
    CUKE_Q_PROPERTY_DECL(bool, FollowSystem)
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
CUKE_NAMESPACE_END

#endif // CUKETHEME_H