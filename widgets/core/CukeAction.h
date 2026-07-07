#ifndef CUKEACTION_H
#define CUKEACTION_H

#include <QAction>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CUKE_EXPORT CukeAction : public QAction {
    Q_OBJECT
    CUKE_Q_PROPERTY_DECL(CukeIconType::Icon, IconType)
public:
    explicit CukeAction(QObject *parent = nullptr);
    explicit CukeAction(const QString &text, QObject *parent = nullptr);
    explicit CukeAction(const CukeIconType::Icon &icon, const QString &text, QObject *parent = nullptr);
    ~CukeAction() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEACTION_H
