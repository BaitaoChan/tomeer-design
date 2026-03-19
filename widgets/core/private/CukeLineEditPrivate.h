#ifndef CUKELINEEDITPRIVATE_H
#define CUKELINEEDITPRIVATE_H
#include "CukeProperty.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(pub)
class CukeLineEdit;
class CukeLineEditPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeLineEdit)
public:
    explicit CukeLineEditPrivate(CukeLineEdit *q);
    ~CukeLineEditPrivate() override;

private:
    bool _isFocused = false;
    bool _hasFocusVisible = false;

    QPropertyAnimation *_borderAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKELINEEDITPRIVATE_H
