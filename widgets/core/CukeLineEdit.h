#ifndef CUKELINEEDIT_H
#define CUKELINEEDIT_H
#include <QLineEdit>

#include "CukeHub.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeLineEditPrivate;
class CUKE_EXPORT CukeLineEdit : public QLineEdit, public CukeHub {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeLineEdit)
    CUKE_Q_PROPERTY_DECL(QColor, BorderColor)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)

public:
    explicit CukeLineEdit(QWidget *parent = nullptr);
    ~CukeLineEdit() override;

protected:
    void focusInEvent(QFocusEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    void onThemeChanged(CukeThemeType::ThemeMode mode) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKELINEEDIT_H
