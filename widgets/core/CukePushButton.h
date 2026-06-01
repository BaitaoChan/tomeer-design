#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukePushButtonPrivate;
class CUKE_EXPORT CukePushButton : public QPushButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukePushButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukePushButton(QWidget* parent = nullptr);
    explicit CukePushButton(QString text, QWidget* parent = nullptr);
    ~CukePushButton() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // PUSHBUTTON_H