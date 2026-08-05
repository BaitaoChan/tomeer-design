#ifndef CUKEAPPBARBUTTONPRIVATE_H
#define CUKEAPPBARBUTTONPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
class QColor;
CUKE_NAMESPACE_BEGIN()
class AppBarButton;
class AppBarButtonStyle;
class AppBarButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(AppBarButton)
public:
    explicit AppBarButtonPrivate(AppBarButton *q);
    ~AppBarButtonPrivate() override;

    Q_SLOT void onHoverChanged();

private:
    QPropertyAnimation *_bgAnim = nullptr;
    QColor *_bgColorFrom = nullptr;
    QColor *_bgColorTo = nullptr;
};

CUKE_NAMESPACE_END

#endif // CUKEAPPBARBUTTONPRIVATE_H