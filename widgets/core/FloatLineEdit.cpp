#include "FloatLineEdit.h"
#include <QKeyEvent>
#include <QtMath>

#include "FloatLineEditPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
FloatLineEdit::FloatLineEdit(QWidget *parent)
    : LineEdit(parent),
      d_ptr(new FloatLineEditPrivate(this)) {

    d_ptr->_validator = new QDoubleValidator(d_ptr->_min, d_ptr->_max, d_ptr->_inputDecimals, this);
    d_ptr->_validator->setNotation(QDoubleValidator::StandardNotation);
    setValidator(d_ptr->_validator);

    setToolTip(QString());

    setDefaultValue(0.0f);
}

FloatLineEdit::~FloatLineEdit() = default;

void FloatLineEdit::setRange(float min, float max) {
    d_ptr->_min = min;
    d_ptr->_max = max;
    d_ptr->_validator->setRange(min, max);

    updateRangeToolTip();
}

void FloatLineEdit::setDefaultValue(float value) {
    value = qBound(d_ptr->_min, value, d_ptr->_max);
    d_ptr->_lastValidValue = value;
    setText(QString::number(value, 'f', d_ptr->_displayDecimals));
}

void FloatLineEdit::setDisplayDecimals(int decimals) {
    d_ptr->_displayDecimals = qMax(0, decimals);
    setText(QString::number(d_ptr->_lastValidValue, 'f', d_ptr->_displayDecimals));

    updateRangeToolTip();
}

int FloatLineEdit::displayDecimals() const {
    return d_ptr->_displayDecimals;
}

void FloatLineEdit::setRangeToolTipEnabled(bool enable) {
    d_ptr->_rangeToolTipEnabled = enable;
    updateRangeToolTip();
}

bool FloatLineEdit::isRangeToolTipEnabled() const {
    return d_ptr->_rangeToolTipEnabled;
}

float FloatLineEdit::value() const {
    return text().toFloat();
}

float FloatLineEdit::lastValidValue() const {
    return d_ptr->_lastValidValue;
}

void FloatLineEdit::focusOutEvent(QFocusEvent *event) {
    validateAndFix();
    LineEdit::focusOutEvent(event);
}

void FloatLineEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return ||
        event->key() == Qt::Key_Enter) {

        validateAndFix(true);
        clearFocus();
        return;
    }
    LineEdit::keyPressEvent(event);
}

void FloatLineEdit::validateAndFix(bool forceEmit) {
    bool ok = false;
    float v = text().toFloat(&ok);

    if (!ok || qIsNaN(v) || v < d_ptr->_min || v > d_ptr->_max) {
        setText(QString::number(d_ptr->_lastValidValue, 'f', d_ptr->_displayDecimals));
        return;
    }

    v = qBound(d_ptr->_min, v, d_ptr->_max);

    setText(QString::number(v, 'f', d_ptr->_displayDecimals));

    if (!qFuzzyCompare(v + 1.0f, d_ptr->_lastValidValue + 1.0f) || forceEmit) {
        d_ptr->_lastValidValue = v;
        emit valueChanged(v);
    }
}

void FloatLineEdit::updateRangeToolTip() {
    if (!d_ptr->_rangeToolTipEnabled) {
        setToolTip(QString());
        return;
    }

    const QString tip = QStringLiteral("范围：[%1 , %2]")
        .arg(QString::number(d_ptr->_min, 'f', d_ptr->_displayDecimals))
        .arg(QString::number(d_ptr->_max, 'f', d_ptr->_displayDecimals));

    setToolTip(tip);
}

CUKE_END_NAMESPACE(widget)