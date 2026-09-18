#include "plain_text_edit_private.h"

#include "plain_text_edit.h"

TOMEER_NAMESPACE_BEGIN()
PlainTextEditPrivate::PlainTextEditPrivate(PlainTextEdit *q)
    : QObject(q),
      q_ptr(q) {
}

PlainTextEditPrivate::~PlainTextEditPrivate() = default;
TOMEER_NAMESPACE_END