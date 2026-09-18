#include "plain_text_edit.h"
#include "plain_text_edit_private.h"

TOMEER_NAMESPACE_BEGIN()
PlainTextEdit::PlainTextEdit(QWidget *parent)
    : QPlainTextEdit(parent),
      d_ptr(new PlainTextEditPrivate(this)) {
}

PlainTextEdit::~PlainTextEdit() = default;

TOMEER_NAMESPACE_END