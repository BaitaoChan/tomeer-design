#ifndef CUKEMENUBAR_H
#define CUKEMENUBAR_H
#include <QMenuBar>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class MenuBarPrivate;
class CUKE_EXPORT MenuBar : public QMenuBar {
    Q_OBJECT
    CUKE_DECLARE_DPTR(MenuBar)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit MenuBar(QWidget* parent = nullptr);
    ~MenuBar() override;

protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END

#endif // CUKEMENUBAR_H