#ifndef CUKEAPPBARBUTTONPRIVATE_H
#define CUKEAPPBARBUTTONPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
class QColor;
CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBarButton;
class CukeAppBarButtonStyle;
class CukeAppBarButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeAppBarButton);
public:
    explicit CukeAppBarButtonPrivate(CukeAppBarButton *q);
    ~CukeAppBarButtonPrivate() override;

    Q_SLOT void onHoverChanged();

private:
    QPropertyAnimation *_bgAnim = nullptr;
    QColor *_bgColorFrom = nullptr;
    QColor *_bgColorTo = nullptr;
};

CUKE_NAMESPACE_END(pub)

#endif // CUKEAPPBARBUTTONPRIVATE_H
