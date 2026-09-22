#ifndef TOGGLE_SWITCH_H
#define TOGGLE_SWITCH_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPainterPath>
#include <QResizeEvent>
#include <QPaintEvent>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ToggleSwitchPrivate;
class WIDGETS_EXPORT ToggleSwitch : public QWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ToggleSwitch)
    TOMEER_Q_PROPERTY_DECL(QColor, BgColor)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ToggleSwitch(QWidget *parent = nullptr);
    ~ToggleSwitch() override;

    void bgColorFrom(QColor color);
    void bgColorTo(QColor color);

    void setIsToggled(bool isToggled);
    bool getIsToggled();

    void setIcon(const QIcon &icon);
    QIcon getIcon();

signals:
    void toggled(bool checked);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent* event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // TOGGLE_SWITCH_H
