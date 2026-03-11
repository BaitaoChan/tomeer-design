#ifndef CUKEWINDOWPRIVATE_H
#define CUKEWINDOWPRIVATE_H

#include "CukeProperty.h"
CUKE_BEGIN_NAMESPACE(widget)
class CukeWindow;
class CukeWindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeWindow)
public:
    explicit CukeWindowPrivate(CukeWindow *q = nullptr);
    ~CukeWindowPrivate() override;
};
CUKE_END_NAMESPACE(widget)

#endif // CUKEWINDOWPRIVATE_H
