#ifndef FLOATLINEEDIT_H
#define FLOATLINEEDIT_H
#include "LineEdit.h"
#include <QDoubleValidator>
CUKE_BEGIN_NAMESPACE(widget)
class FloatLineEditPrivate;
class CUKE_EXPORT FloatLineEdit : public LineEdit {
    Q_OBJECT
    CUKE_DECLARE_DPTR(FloatLineEdit)
public:
    explicit FloatLineEdit(QWidget *parent = nullptr);
    ~FloatLineEdit() override;

    void setRange(float min, float max);

    void setDefaultValue(float value);

    void setDisplayDecimals(int decimals);
    int  displayDecimals() const;

    void setRangeToolTipEnabled(bool enable);
    bool isRangeToolTipEnabled() const;

    float value() const;
    float lastValidValue() const;

signals:
    void valueChanged(float value);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    void validateAndFix(bool forceEmit = false);
    void updateRangeToolTip();
};
CUKE_END_NAMESPACE(widget)

#endif // FLOATLINEEDIT_H