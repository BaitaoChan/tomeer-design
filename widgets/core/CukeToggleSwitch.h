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

#include "CukeContext.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToggleSwitchPrivate;
class CUKE_EXPORT CukeToggleSwitch : public QWidget, public CukeContext {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToggleSwitch)
    CUKE_Q_PROPERTY_DECL(QColor, BgColor)
    CUKE_Q_PROPERTY_DECL(QColor, KnobColor)
    CUKE_Q_PROPERTY_DECL(qreal, KnobDiameter)
    CUKE_Q_PROPERTY_DECL(qreal, KnobCenterY)
    CUKE_Q_PROPERTY_DECL(qreal, KnobCenterX)

public:
    explicit CukeToggleSwitch(QWidget *parent = nullptr);
    ~CukeToggleSwitch() override;

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
    void onThemeChanged(CukeThemeType::ThemeMode Mode) override;
};
CUKE_NAMESPACE_END(pub)

#endif // TOGGLESWITCH_H
