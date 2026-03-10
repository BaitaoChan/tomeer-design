#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include "QPushButton.h"
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QPainter>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class ToggleButtonPrivate;
class CUKE_EXPORT ToggleButton : public ContextMixin<QPushButton> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToggleButton)
public:
    explicit ToggleButton(QWidget* parent = nullptr);
    explicit ToggleButton(const QString& text, QWidget* parent = nullptr);
    ~ToggleButton() override;

    void setBorderRadius(int radius);

    void setIsToggled(bool isToggled);
    bool getIsToggled() const;

signals:
    void toggled(bool checked);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
};
CUKE_END_NAMESPACE(widget)

#endif // TOGGLEBUTTON_H
