#ifndef CUKEMAINWINDOW_H
#define CUKEMAINWINDOW_H
#include <QMainWindow>

#include "CukeContextMixin.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeWindowPrivate;
class CUKE_EXPORT CukeWindow : public CukeContextMixin<QMainWindow> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeWindow)
public:
    explicit CukeWindow(QWidget *parent = nullptr);
    ~CukeWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEMAINWINDOW_H
