#ifndef PLAIN_TEXT_EDIT_PRIVATE_H
#define PLAIN_TEXT_EDIT_PRIVATE_H
#include "property.h"
#include "type.h"

class QPropertyAnimation;
TOMEER_NAMESPACE_BEGIN()
class PlainTextEdit;
class PlainTextEditPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(PlainTextEdit)
public:
    explicit PlainTextEditPrivate(PlainTextEdit *q);
    ~PlainTextEditPrivate() override;

private:
    bool _isFocused = false;

    QPropertyAnimation *_lineAnim = nullptr;
};
TOMEER_NAMESPACE_END

#endif // PLAIN_TEXT_EDIT_PRIVATE_H
