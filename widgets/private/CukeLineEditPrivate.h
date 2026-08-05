#ifndef CUKELINEEDITPRIVATE_H
#define CUKELINEEDITPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN()
class LineEdit;
class LineEditPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(LineEdit)
public:
    explicit LineEditPrivate(LineEdit *q);
    ~LineEditPrivate() override;

private:
    bool _isFocused = false;

    QPropertyAnimation *_lineAnim = nullptr;
};
CUKE_NAMESPACE_END


#endif // CUKELINEEDITPRIVATE_H