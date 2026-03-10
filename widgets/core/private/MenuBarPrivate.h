#ifndef MENUBARPRIVATE_H
#define MENUBARPRIVATE_H
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class MenuBar;
class MenuBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(MenuBar)
public:
    explicit MenuBarPrivate(MenuBar *q);
    ~MenuBarPrivate() override;
};
CUKE_END_NAMESPACE(widget)

#endif // MENUBARPRIVATE_H
