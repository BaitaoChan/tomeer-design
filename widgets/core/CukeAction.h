#ifndef CUKEACTION_H
#define CUKEACTION_H

#include <QAction>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ActionPrivate;
class CUKE_EXPORT Action : public QAction {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Action)
    CUKE_Q_PROPERTY_DECL(IconType::Icon, IconType)
public:
    explicit Action(QObject *parent = nullptr);
    explicit Action(const QString &text, QObject *parent = nullptr);
    explicit Action(const QIcon &icon, const QString &text, QObject *parent = nullptr);
    explicit Action(const IconType::Icon &icon, const QString &text, QObject *parent = nullptr);
    ~Action() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEACTION_H
