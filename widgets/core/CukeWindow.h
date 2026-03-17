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
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
public:
    explicit CukeWindow(QWidget *parent = nullptr);
    ~CukeWindow() override;

    inline void resize(int w, int h);
    // void setCentralWidget(QWidget *widget);

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEMAINWINDOW_H
