#ifndef CUKELINEEDITPRIVATE_H
#define CUKELINEEDITPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QPropertyAnimation;
CUKE_NAMESPACE_BEGIN(pub)
class LineEdit;
class LineEditPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(LineEdit)
public:
    explicit LineEditPrivate(LineEdit *q);
    ~LineEditPrivate() override;

    Q_SLOT void onLineAnimFinished();

private:
    bool _isFocused = false;
    bool _hasFocusVisible = false;

    QPropertyAnimation *_borderAnim = nullptr;
    QPropertyAnimation *_lineAnim = nullptr;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKELINEEDITPRIVATE_H