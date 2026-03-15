#ifndef CUKETHEME_H
#define CUKETHEME_H
#include <QColor>
#include "CukeType.h"
#include "CukeProperty.h"

#define pTheme CukeTheme::instance()
#define pThemeColor(Mode, Color) pTheme->getThemeColor(Mode, CukeThemeType::Color)

CUKE_NAMESPACE_BEGIN(widget)
class CukeThemePrivate;
class CUKE_EXPORT CukeTheme : public QObject {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeTheme)
    CUKE_Q_SINGLETON_DECL(CukeTheme)
private:
    explicit CukeTheme(QObject *parent = nullptr);
    ~CukeTheme() override;

public:
    void setThemeMode(CukeThemeType::ThemeMode Mode);
    CukeThemeType::ThemeMode getThemeMode() const;

    void addThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color, QColor newColor);
    const QColor& getThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color);
signals:
    void themeModeChanged(CukeThemeType::ThemeMode Mode);

private:
    void initThemeColor();
};
CUKE_NAMESPACE_END(widget)

#endif // CUKETHEME_H
