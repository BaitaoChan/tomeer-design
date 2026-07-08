#ifndef SLIDER_H
#define SLIDER_H
#include <QSlider>
#include <QStyleOptionSlider>
#include <QPainter>
#include <QPropertyAnimation>
#include <QMouseEvent>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class SliderPrivate;
class CUKE_EXPORT Slider : public QSlider {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Slider)
    CUKE_Q_PROPERTY_DECL(qreal, HandleDiameter)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit Slider(QWidget *parent = nullptr);
    explicit Slider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~Slider() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // SLIDER_H
