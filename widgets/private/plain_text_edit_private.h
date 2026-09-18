#ifndef PLAIN_TEXT_EDIT_PRIVATE_H
#define PLAIN_TEXT_EDIT_PRIVATE_H
#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class PlainTextEdit;
class PlainTextEditPrivate : public QObject {
    Q_OBJECT
    TOMEER_DECLARE_QPTR(PlainTextEdit)
public:
    explicit PlainTextEditPrivate(PlainTextEdit *q);
    ~PlainTextEditPrivate() override;
};
TOMEER_NAMESPACE_END

#endif // PLAIN_TEXT_EDIT_PRIVATE_H