#ifndef CUKESCOPE_H
#define CUKESCOPE_H
#define CUKE_ELEM(OBJECT, TYPE, KEY) static_cast<TYPE *>((OBJECT)->findElem(KEY))
#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeScopePrivate;
class CUKE_EXPORT CukeScope {
    CUKE_DECLARE_DPTR(CukeScope)
public:
    explicit CukeScope(QObject *child);
    virtual ~CukeScope();

    void setThemeMode(CukeThemeType::ThemeMode mode);
    CukeThemeType::ThemeMode getThemeMode() const;

    void addElem(int key, void *child) const;
    void *findElem(int key) const;
    QList<void *> findElems() const;
    bool hasElem(int key) const;


protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKESCOPE_H