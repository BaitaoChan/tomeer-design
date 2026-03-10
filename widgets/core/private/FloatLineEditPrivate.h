#ifndef FLOATLINEEDITPRIVATE_H
#define FLOATLINEEDITPRIVATE_H
#include "Property.h"

class QDoubleValidator;
CUKE_BEGIN_NAMESPACE(widget)
class FloatLineEdit;
class FloatLineEditPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(FloatLineEdit)
public:
    explicit FloatLineEditPrivate(FloatLineEdit *q);
    ~FloatLineEditPrivate() override;

private:
    float _min = -1e9f;
    float _max =  1e9f;

    int   _displayDecimals = 2;
    int   _inputDecimals   = 10;

    float _lastValidValue = 0.0f;

    bool _rangeToolTipEnabled = false;

    QDoubleValidator *_validator = nullptr;
};
CUKE_END_NAMESPACE(widget)


#endif // FLOATLINEEDITPRIVATE_H
