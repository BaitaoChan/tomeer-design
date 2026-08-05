#ifndef CUKEMENUBARPRIVATE_H
#define CUKEMENUBARPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN()
class MenuBar;
class MenuBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(MenuBar)
public:
    explicit MenuBarPrivate(MenuBar *q);
    ~MenuBarPrivate() override;
};
CUKE_NAMESPACE_END

#endif // CUKEMENUBARPRIVATE_H