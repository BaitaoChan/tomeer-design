#ifndef CUKEAPPBARPRIVATE_H
#define CUKEAPPBARPRIVATE_H
#include "CukeProperty.h"

class QHBoxLayout;
class QVBoxLayout;
class QIcon;
class QLabel;
CUKE_NAMESPACE_BEGIN(widget)
class CukeAppBar;
class CukeLabel;
class CukeAppBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeAppBar)
public:
    explicit CukeAppBarPrivate(CukeAppBar *q);
    ~CukeAppBarPrivate() override;

private:
    QHBoxLayout *_layout = nullptr;
    CukeLabel *_windowTitle = nullptr;
    QLabel *_windowIcon = nullptr;


};
CUKE_NAMESPACE_END(widget)

#endif //CUKEAPPBARPRIVATE_H
