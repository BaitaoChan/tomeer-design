#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>
#include <QStyleOptionSlider>
#include <QPainter>
#include <QPropertyAnimation>
#include <QMouseEvent>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class SliderPrivate;
class WIDGETS_EXPORT Slider : public QSlider {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(Slider)
    TOMEER_Q_PROPERTY_DECL(qreal, HandleDiameter)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit Slider(QWidget *parent = nullptr);
    explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~Slider() override;

protected:
    bool event(QEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // SLIDER_H