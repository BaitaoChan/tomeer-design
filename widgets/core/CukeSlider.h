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
class CukeSliderPrivate;
class CUKE_EXPORT CukeSlider : public QSlider {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeSlider)
    CUKE_Q_PROPERTY_DECL(qreal, HandleDiameter)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeSlider(QWidget *parent = nullptr);
    explicit CukeSlider(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~CukeSlider() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // SLIDER_H
