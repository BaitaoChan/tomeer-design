#ifndef CUKEHUB_H
#define CUKEHUB_H
#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeContextPrivate;
class CUKE_EXPORT CukeHub {
    CUKE_DECLARE_DPTR(CukeContext)
public:
    explicit CukeHub(QObject *child);
    virtual ~CukeHub();

    void setThemeMode(CukeThemeType::ThemeMode mode);
    CukeThemeType::ThemeMode getThemeMode() const;

protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEHUB_H