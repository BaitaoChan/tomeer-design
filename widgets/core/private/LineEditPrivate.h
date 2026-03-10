#ifndef LINEEDITPRIVATE_H
#define LINEEDITPRIVATE_H
#include "Property.h"

class QPropertyAnimation;
CUKE_BEGIN_NAMESPACE(widget)
class LineEdit;
class LineEditPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(LineEdit)
public:
    explicit LineEditPrivate(LineEdit *q);
    ~LineEditPrivate() override;

private:
    bool _isFocused = false;
    bool _hasFocusVisible = false;

    QPropertyAnimation *_borderAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
};
CUKE_END_NAMESPACE(widget)


#endif // LINEEDITPRIVATE_H
