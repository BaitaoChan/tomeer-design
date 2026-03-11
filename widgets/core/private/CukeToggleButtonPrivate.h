#ifndef CUKETOGGLEBUTTONPRIVATE_H
#define CUKETOGGLEBUTTONPRIVATE_H
#include <QColor>

#include "CukeProperty.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeToggleButton;
class CukeToggleButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeToggleButton)
public:
    explicit CukeToggleButtonPrivate(CukeToggleButton *q);
    ~CukeToggleButtonPrivate() override;

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


#endif // CUKETOGGLEBUTTONPRIVATE_H
