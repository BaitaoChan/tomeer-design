#ifndef CUKEWINDOWPRIVATE_H
#define CUKEWINDOWPRIVATE_H

#include "CukeProperty.h"
class QVBoxLayout;
class QMainWindow;
CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBar;
class CukeWindow;
class CukeWindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeWindow)
    CUKE_Q_PROPERTY_DECL(bool, IsResize)
    CUKE_Q_PROPERTY_DECL(bool, IsDrag)
public:
    explicit CukeWindowPrivate(CukeWindow *q = nullptr);
    ~CukeWindowPrivate() override;

private:
    QWidget *_widget = nullptr;
    QVBoxLayout *_layout = nullptr;
    CukeAppBar *_appBar = nullptr;
    QMainWindow *_window = nullptr;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEWINDOWPRIVATE_H
