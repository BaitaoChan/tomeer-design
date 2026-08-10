#ifndef APP_BAR_BUTTON_PRIVATE_H
#define APP_BAR_BUTTON_PRIVATE_H
#include "property.h"
#include "type.h"

class QPropertyAnimation;
class QColor;
TOMEER_NAMESPACE_BEGIN()
class AppBarButton;
class AppBarButtonStyle;
class AppBarButtonPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(AppBarButton)
public:
    explicit AppBarButtonPrivate(AppBarButton *q);
    ~AppBarButtonPrivate() override;

    Q_SLOT void onHoverChanged();

private:
    QPropertyAnimation *_bgAnim = nullptr;
    QColor *_bgColorFrom = nullptr;
    QColor *_bgColorTo = nullptr;
};

TOMEER_NAMESPACE_END

#endif // APP_BAR_BUTTON_PRIVATE_H