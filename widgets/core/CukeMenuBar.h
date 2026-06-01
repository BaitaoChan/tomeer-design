#ifndef CUKEMENUBAR_H
#define CUKEMENUBAR_H
#include <QMenuBar>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenuBarPrivate;
class CUKE_EXPORT CukeMenuBar : public QMenuBar {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeMenuBar)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeMenuBar(QWidget* parent = nullptr);
    ~CukeMenuBar() override;

protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUBAR_H
