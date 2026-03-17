#ifndef CUKEWINDOWPRIVATE_H
#define CUKEWINDOWPRIVATE_H

#include "CukeProperty.h"
class QVBoxLayout;
CUKE_NAMESPACE_BEGIN(widget)
class CukeAppBar;
class CukeWindow;
class CukeWindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeWindow)
public:
    explicit CukeWindowPrivate(CukeWindow *q = nullptr);
    ~CukeWindowPrivate() override;

private:
    QWidget *_widget = nullptr;
    QVBoxLayout *_layout = nullptr;
    CukeAppBar *_appBar = nullptr;
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEWINDOWPRIVATE_H
