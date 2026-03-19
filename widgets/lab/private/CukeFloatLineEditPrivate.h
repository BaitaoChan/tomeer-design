#ifndef CUKEFLOATLINEEDITPRIVATE_H
#define CUKEFLOATLINEEDITPRIVATE_H
#include "CukeProperty.h"

class QDoubleValidator;
CUKE_NAMESPACE_BEGIN(lab)
class CukeFloatLineEdit;
class CukeFloatLineEditPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeFloatLineEdit)
public:
    explicit CukeFloatLineEditPrivate(CukeFloatLineEdit *q);
    ~CukeFloatLineEditPrivate() override;

private:
    float _min = -1e9f;
    float _max =  1e9f;

    int   _displayDecimals = 2;
    int   _inputDecimals   = 10;

    float _lastValidValue = 0.0f;

    bool _rangeToolTipEnabled = false;

    QDoubleValidator *_validator = nullptr;
};
CUKE_NAMESPACE_END(lab)


#endif // CUKEFLOATLINEEDITPRIVATE_H
