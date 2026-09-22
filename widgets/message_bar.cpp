#include "message_bar.h"
#include "message_bar_private.h"

TOMEER_NAMESPACE_BEGIN()
MessageBar::MessageBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new MessageBarPrivate(this)) {
}

MessageBar::~MessageBar() = default;

TOMEER_NAMESPACE_END
