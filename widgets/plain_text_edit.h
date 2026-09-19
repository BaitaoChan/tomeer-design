#ifndef PLAIN_TEXT_EDIT_H
#define PLAIN_TEXT_EDIT_H
#include <QPlainTextEdit>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class PlainTextEditPrivate;
class WIDGETS_EXPORT PlainTextEdit : public QPlainTextEdit {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(PlainTextEdit)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(int, LineHalfWidth)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit PlainTextEdit(QWidget *parent = nullptr);
    explicit PlainTextEdit(const QString &text, QWidget *parent = nullptr);
    ~PlainTextEdit() override;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // PLAIN_TEXT_EDIT_H