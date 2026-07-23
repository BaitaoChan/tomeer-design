#ifndef CUKELINEEDIT_H
#define CUKELINEEDIT_H
#include <QLineEdit>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class LineEditPrivate;
class CUKE_EXPORT LineEdit : public QLineEdit {
    Q_OBJECT
    CUKE_DECLARE_DPTR(LineEdit)
    CUKE_Q_PROPERTY_DECL(QColor, BorderColor)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
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
CUKE_NAMESPACE_END(pub)

#endif // CUKELINEEDIT_H