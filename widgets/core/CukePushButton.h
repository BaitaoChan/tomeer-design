#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>

#include <QMouseEvent>
#include <QPainter>
#include <QStyleOptionButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class PushButtonPrivate;
class CUKE_EXPORT PushButton : public QPushButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(PushButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit PushButton(QWidget* parent = nullptr);
    explicit PushButton(const QString& text, QWidget* parent = nullptr);
    ~PushButton() override;

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // PUSHBUTTON_H