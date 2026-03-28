#ifndef CUKETOOLBUTTONPRIVATE_H
#define CUKETOOLBUTTONPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
class QColor;
CUKE_NAMESPACE_BEGIN(pub)
class CukeToolButton;
class CukeToolButtonStyle;
class CukeToolButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeToolButton)
public:
    explicit CukeToolButtonPrivate(CukeToolButton *parent = nullptr);
    ~CukeToolButtonPrivate() override;

    Q_SLOT void onHoverChanged();

private:
    CukeToolButtonStyle *_style = nullptr;

    QPropertyAnimation *_bgAnim = nullptr;
    QColor *_bgColorFrom = nullptr;
    QColor *_bgColorTo = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBUTTONPRIVATE_H
