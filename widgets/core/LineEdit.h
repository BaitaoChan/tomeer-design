#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include <QPropertyAnimation>
#include <QPainter>
#include <QStyleOptionFrame>
#include "ContextMixin.h"
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class LineEditPrivate;
class CUKE_EXPORT LineEdit : public ContextMixin<QLineEdit> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(LineEdit)
    CUKE_Q_PROPERTY_DECL(QColor, BorderColor)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)

public:
    explicit LineEdit(QWidget *parent = nullptr);
    ~LineEdit() override;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void onThemeChanged(ThemeType::Mode mode) override;
};
CUKE_END_NAMESPACE(widget)

#endif // LINEEDIT_H
