#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMenuBar>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class MenuBarPrivate;
class CUKE_EXPORT MenuBar : public ContextMixin<QMenuBar> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(MenuBar)
public:
    explicit MenuBar(QWidget* parent = nullptr);
    ~MenuBar() override;
};
CUKE_END_NAMESPACE(widget)

#endif // MENUBAR_H
