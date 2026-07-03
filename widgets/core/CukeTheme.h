#ifndef CUKETHEME_H
#define CUKETHEME_H
#include <QColor>
#include "CukeType.h"
#include "CukeProperty.h"

#define CUKE_THEME CukeTheme::instance()

CUKE_NAMESPACE_BEGIN(pub)
class CukeThemePrivate;
class CUKE_EXPORT CukeTheme : public QObject {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeTheme)
    CUKE_Q_SINGLETON_DECL(CukeTheme)
private:
    explicit CukeTheme(QObject *parent = nullptr);
    ~CukeTheme() override;

public:
    void setThemeMode(CukeThemeType::ThemeMode mode);
    CukeThemeType::ThemeMode getThemeMode();

    void addThemeColor(CukeThemeType::ThemeMode mode, CukeThemeType::ThemeColor color, QColor newColor);
    QColor getThemeColor(CukeThemeType::ThemeMode mode, CukeThemeType::ThemeColor color);
signals:
    void themeModeChanged(CukeThemeType::ThemeMode mode);
private:
    void initThemeColor();
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETHEME_H
