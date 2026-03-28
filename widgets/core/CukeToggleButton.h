#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include "QPushButton.h"
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QPainter>

#include "CukeScope.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToggleButtonPrivate;
class CUKE_EXPORT CukeToggleButton : public QPushButton, public CukeScope {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToggleButton)
public:
    explicit CukeToggleButton(QWidget* parent = nullptr);
    explicit CukeToggleButton(const QString& text, QWidget* parent = nullptr);
    ~CukeToggleButton() override;

    void setBorderRadius(int radius);

    void setIsToggled(bool isToggled);
    bool getIsToggled();

signals:
    void toggled(bool checked);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // TOGGLEBUTTON_H
