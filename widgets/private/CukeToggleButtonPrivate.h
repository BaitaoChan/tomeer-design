#ifndef CUKETOGGLEBUTTONPRIVATE_H
#define CUKETOGGLEBUTTONPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class ToggleButton;
class ToggleButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ToggleButton)
public:
    explicit ToggleButtonPrivate(ToggleButton *q);
    ~ToggleButtonPrivate() override;

};
CUKE_NAMESPACE_END

#endif // CUKETOGGLEBUTTONPRIVATE_H