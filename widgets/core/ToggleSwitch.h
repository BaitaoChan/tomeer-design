#ifndef TOGGLESWITCH_H
#define TOGGLESWITCH_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPainterPath>
#include <QResizeEvent>
#include <QPaintEvent>

#include "ContextMixin.h"
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class ToggleSwitchPrivate;
class CUKE_EXPORT ToggleSwitch : public ContextMixin<QWidget> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToggleSwitch)
    CUKE_Q_PROPERTY_DECL(QColor, BgColor)
    CUKE_Q_PROPERTY_DECL(QColor, KnobColor)
    CUKE_Q_PROPERTY_DECL(qreal, KnobDiameter)
    CUKE_Q_PROPERTY_DECL(qreal, KnobCenterY)
    CUKE_Q_PROPERTY_DECL(qreal, KnobCenterX)

public:
    explicit ToggleSwitch(QWidget *parent = nullptr);
    ~ToggleSwitch() override;

    void setIsToggled(bool isToggled);
    bool getIsToggled() const;

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

private slots:
    void onThemeChanged(ThemeType::Mode Mode) override;
};
CUKE_END_NAMESPACE(widget)

#endif // TOGGLESWITCH_H
