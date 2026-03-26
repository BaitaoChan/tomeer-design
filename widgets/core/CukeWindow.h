#ifndef CUKEMAINWINDOW_H
#define CUKEMAINWINDOW_H
#include <QMainWindow>

#include "CukeHub.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeWindowPrivate;
class CUKE_EXPORT CukeWindow : public QMainWindow, public CukeHub {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeWindow)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
public:
    explicit CukeWindow(QWidget *parent = nullptr);
    ~CukeWindow() override;

    inline void resize(int w, int h);
    // void setCentralWidget(QWidget *widget);

protected:
    void showEvent(QShowEvent *event) override;
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMAINWINDOW_H
