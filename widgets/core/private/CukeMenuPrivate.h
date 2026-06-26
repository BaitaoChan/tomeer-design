#ifndef CUKEMENUPRIVATE_H
#define CUKEMENUPRIVATE_H
#include "CukeMenu.h"
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenu;
class CukeMenuPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeMenu)
public:
    explicit CukeMenuPrivate(CukeMenu *q);
    ~CukeMenuPrivate() override;

};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUPRIVATE_H
