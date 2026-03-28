#ifndef CUKESCOPE_H
#define CUKESCOPE_H
#define CUKE_ELEM(OBJECT, TYPE, NAME) static_cast<TYPE *>((OBJECT)->findElem(NAME))
#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeHubPrivate;
class CUKE_EXPORT CukeScope {
    CUKE_DECLARE_DPTR(CukeHub)
public:
    explicit CukeScope(QObject *child);
    virtual ~CukeScope();

    void setThemeMode(CukeThemeType::ThemeMode mode);
    CukeThemeType::ThemeMode getThemeMode() const;

    void addElem(const QString &name, void *child) const;
    void *findElem(const QString &name) const;
    QList<void *> findElems() const;
    bool hasElem(const QString &name) const;


protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCOPE_H