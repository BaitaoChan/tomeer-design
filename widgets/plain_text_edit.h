#ifndef PLAIN_TEXT_EDIT_H
#define PLAIN_TEXT_EDIT_H
#include <QPlainTextEdit>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class PlainTextEditPrivate;
class WIDGETS_EXPORT PlainTextEdit : public QPlainTextEdit {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(PlainTextEdit)
public:
    explicit PlainTextEdit(QWidget *parent = nullptr);
    ~PlainTextEdit() override;
};
TOMEER_NAMESPACE_END

#endif // PLAIN_TEXT_EDIT_H