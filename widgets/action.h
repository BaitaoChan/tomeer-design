#ifndef ACTION_H
#define ACTION_H

#include <QAction>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class ActionPrivate;
class WIDGETS_EXPORT Action : public QAction {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(Action)
    TOMEER_Q_PROPERTY_DECL(IconType::Icon, Icon)
public:
    using QAction::setIcon;

    explicit Action(QObject *parent = nullptr);
    explicit Action(const QString &text, QObject *parent = nullptr);
    explicit Action(const QIcon &icon, const QString &text, QObject *parent = nullptr);
    explicit Action(const IconType::Icon &icon, const QString &text, QObject *parent = nullptr);
    ~Action() override;
};
TOMEER_NAMESPACE_END

#endif // ACTION_H
