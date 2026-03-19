#ifndef CUKETOGGLEBUTTONPRIVATE_H
#define CUKETOGGLEBUTTONPRIVATE_H
#include <QColor>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
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
CUKE_NAMESPACE_END(pub)


#endif // CUKETOGGLEBUTTONPRIVATE_H
