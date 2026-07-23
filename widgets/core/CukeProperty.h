#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>
#include <QtCore/qglobal.h>

#if defined(CUKEWIDGETS_LIBRARY)
#define CUKE_EXPORT Q_DECL_EXPORT
#else
#define CUKE_EXPORT Q_DECL_IMPORT
#endif

#define CUKE_Q_PROPERTY_INLINE(TYPE, NAME)                                              \
    Q_PROPERTY(TYPE _p##NAME READ get##NAME WRITE set##NAME NOTIFY p##NAME##Changed)    \
public:                                                                                 \
    Q_SIGNAL void p##NAME##Changed();                                                   \
    void set##NAME(TYPE p##NAME) {                                                      \
        if (_p##NAME != p##NAME) {                                                      \
            _p##NAME = p##NAME;                                                         \
            Q_EMIT p##NAME##Changed();                                                  \
        }                                                                               \
    }                                                                                   \
    TYPE get##NAME() const {                                                            \
        return _p##NAME;                                                                \
    }                                                                                   \
private:                                                                                \
    TYPE _p##NAME{};

#define CUKE_Q_PROPERTY_DECL(TYPE, NAME)                                                \
    Q_PROPERTY(TYPE _p##NAME READ get##NAME WRITE set##NAME NOTIFY p##NAME##Changed)    \
public:                                                                                 \
    Q_SIGNAL void p##NAME##Changed();                                                   \
    void set##NAME(TYPE p##NAME);                                                       \
    TYPE get##NAME() const;                                                             \
private:                                                                                \
    TYPE _p##NAME{};

#define CUKE_Q_PROPERTY_IMPL(CLASS, TYPE, NAME)                                         \
void CLASS::set##NAME(TYPE p##NAME) {                                                   \
    if (_p##NAME != p##NAME) {                                                          \
        _p##NAME = p##NAME;                                                             \
        Q_EMIT p##NAME##Changed();                                                      \
    }                                                                                   \
}                                                                                       \
TYPE CLASS::get##NAME() const {                                                         \
    return _p##NAME;                                                                    \
}

#define CUKE_Q_SINGLETON_DECL(CLASS)                                                    \
public:                                                                                 \
    static CLASS *instance();

#define CUKE_Q_SINGLETON_IMPL(CLASS)                                                    \
CLASS *CLASS::instance() {                                                              \
    static CLASS instance;                                                              \
    return &instance;                                                                   \
}

#define CUKE_DECLARE_DPTR(CLASS)                                                        \
private:                                                                                \
    Q_DECLARE_PRIVATE(CLASS)                                                            \
    QScopedPointer<CLASS##Private> d_ptr;

#define CUKE_DECLARE_QPTR(CLASS)                                                        \
private:                                                                                \
    Q_DECLARE_PUBLIC(CLASS)                                                             \
    CLASS *q_ptr = nullptr;

#define CUKE_NAMESPACE_BEGIN(NAME)                                                      \
namespace cuke::NAME {

#define CUKE_NAMESPACE_END(NAME)                                                        \
}

#endif // PROPERTY_H