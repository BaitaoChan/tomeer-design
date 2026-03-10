#ifndef WINDOW_H
#define WINDOW_H
#include <QMainWindow>

#include "ContextMixin.h"
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class WindowPrivate;
class CUKE_EXPORT Window : public ContextMixin<QMainWindow> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Window)
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window() override;
};
CUKE_END_NAMESPACE(widget)

#endif // WINDOW_H
