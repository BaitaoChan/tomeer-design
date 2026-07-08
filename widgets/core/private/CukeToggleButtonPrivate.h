#ifndef CUKETOGGLEBUTTONPRIVATE_H
#define CUKETOGGLEBUTTONPRIVATE_H
#include <QColor>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToggleButton;
class ToggleButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(ToggleButton)
public:
    explicit ToggleButtonPrivate(ToggleButton *q);
    ~ToggleButtonPrivate() override;

private:

    bool _isPressed = false, _isHovered = false, _isToggled = false;
    int _borderRadius = 6;

    QColor defaultColor = QColor();
    QColor hoverColor = QColor();
    QColor pressColor = QColor();
    QColor checkColor = QColor();
    QColor textColor = QColor();
};
CUKE_NAMESPACE_END(pub)


#endif // CUKETOGGLEBUTTONPRIVATE_H
