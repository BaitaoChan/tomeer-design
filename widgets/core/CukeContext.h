#ifndef CUKECONTEXT_H
#define CUKECONTEXT_H
#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeContextPrivate;
class CUKE_EXPORT CukeContext {
    CUKE_DECLARE_DPTR(CukeContext)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeContext(QObject *child);
    virtual ~CukeContext();

protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECONTEXT_H