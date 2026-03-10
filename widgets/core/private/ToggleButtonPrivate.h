#ifndef TOGGLEBUTTONPRIVATE_H
#define TOGGLEBUTTONPRIVATE_H
#include <QColor>

#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
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
CUKE_END_NAMESPACE(widget)


#endif // TOGGLEBUTTONPRIVATE_H
