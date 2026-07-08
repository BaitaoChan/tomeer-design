#ifndef CUKEMENUPRIVATE_H
#define CUKEMENUPRIVATE_H
#include "CukeMenu.h"
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class Menu;
class MenuPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Menu)
public:
    explicit MenuPrivate(Menu *q);
    ~MenuPrivate() override;

};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUPRIVATE_H
