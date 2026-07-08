#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H
#include "QPushButton.h"
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QPainter>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToggleButtonPrivate;
class CUKE_EXPORT ToggleButton : public QPushButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToggleButton)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ToggleButton(QWidget* parent = nullptr);
    explicit ToggleButton(const QString& text, QWidget* parent = nullptr);
    ~ToggleButton() override;

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

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // TOGGLEBUTTON_H
