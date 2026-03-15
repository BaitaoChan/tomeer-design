#ifndef CUKEWINDOWPRIVATE_H
#define CUKEWINDOWPRIVATE_H

#include "CukeProperty.h"
CUKE_NAMESPACE_BEGIN(widget)
class CukeWindow;
class CukeWindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeWindow)
public:
    explicit CukeWindowPrivate(CukeWindow *q = nullptr);
    ~CukeWindowPrivate() override;
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEWINDOWPRIVATE_H
