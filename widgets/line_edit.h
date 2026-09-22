#ifndef LINE_EDIT_H
#define LINE_EDIT_H
#include <QLineEdit>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class LineEditPrivate;
class WIDGETS_EXPORT LineEdit : public QLineEdit {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(LineEdit)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(int, LineHalfWidth)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit LineEdit(QWidget *parent = nullptr);
    ~LineEdit() override;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // LINE_EDIT_H
