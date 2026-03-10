#include "Window.h"
#include "WindowStyle.h"
#include "WindowPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
Window::Window(QWidget *parent)
    : ContextMixin(parent),
      d_ptr(new WindowPrivate(this)) {
    resize(1280, 720);
}

Window::~Window() = default;

CUKE_END_NAMESPACE(widget)