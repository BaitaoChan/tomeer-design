#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "QPushButton.h"

#include "ContextMixin.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionButton>

#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class PushButtonPrivate;
class CUKE_EXPORT PushButton : public ContextMixin<QPushButton> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(PushButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
public:
    explicit PushButton(QWidget* parent = nullptr);
    explicit PushButton(QString text, QWidget* parent = nullptr);
    ~PushButton() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
};
CUKE_END_NAMESPACE(widget)

#endif // PUSHBUTTON_H