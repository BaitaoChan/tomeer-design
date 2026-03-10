#ifndef WINDOWPRIVATE_H
#define WINDOWPRIVATE_H

#include "Property.h"
CUKE_BEGIN_NAMESPACE(widget)
class Window;
class WindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(Window)
public:
    explicit WindowPrivate(Window *q = nullptr);
    ~WindowPrivate() override;
};
CUKE_END_NAMESPACE(widget)

#endif // WINDOWPRIVATE_H
