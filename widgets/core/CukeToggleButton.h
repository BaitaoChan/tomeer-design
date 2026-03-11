#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include "QPushButton.h"
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QPainter>

#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeToggleButtonPrivate;
class CUKE_EXPORT CukeToggleButton : public CukeContextMixin<QPushButton> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToggleButton)
public:
    explicit CukeToggleButton(QWidget* parent = nullptr);
    explicit CukeToggleButton(const QString& text, QWidget* parent = nullptr);
    ~CukeToggleButton() override;

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
