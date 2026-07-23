#ifndef CUKETOGGLESWITCH_H
#define CUKETOGGLESWITCH_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPainterPath>
#include <QResizeEvent>
#include <QPaintEvent>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToggleSwitchPrivate;
class CUKE_EXPORT ToggleSwitch : public QWidget {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToggleSwitch)
    CUKE_Q_PROPERTY_DECL(QColor, BgColor)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
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
CUKE_NAMESPACE_END(pub)

#endif // CUKETOGGLESWITCH_H