#ifndef CUKEFLOATLINEEDIT_H
#define CUKEFLOATLINEEDIT_H
#include <QDoubleValidator>
#include "CukeLineEdit.h"

using namespace cuke::pub;

CUKE_NAMESPACE_BEGIN(lab)
class CukeFloatLineEditPrivate;
class CUKE_EXPORT CukeFloatLineEdit : public CukeLineEdit {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeFloatLineEdit)
public:
    explicit CukeFloatLineEdit(QWidget *parent = nullptr);
    ~CukeFloatLineEdit() override;

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
CUKE_NAMESPACE_END(lab)

#endif // CUKEFLOATLINEEDIT_H