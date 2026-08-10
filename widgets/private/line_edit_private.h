#ifndef LINE_EDIT_PRIVATE_H
#define LINE_EDIT_PRIVATE_H
#include "property.h"
#include "type.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class LineEdit;
class LineEditPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(LineEdit)
public:
    explicit LineEditPrivate(LineEdit *q);
    ~LineEditPrivate() override;

private:
    bool _isFocused = false;

    QPropertyAnimation *_lineAnim = nullptr;
};
TOMEER_NAMESPACE_END


#endif // LINE_EDIT_PRIVATE_H