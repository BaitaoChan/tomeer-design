#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "QPushButton.h"

#include "CukeContextMixin.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionButton>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukePushButtonPrivate;
class CUKE_EXPORT CukePushButton : public CukeContextMixin<QPushButton> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukePushButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
public:
    explicit CukePushButton(QWidget* parent = nullptr);
    explicit CukePushButton(QString text, QWidget* parent = nullptr);
    ~CukePushButton() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // PUSHBUTTON_H