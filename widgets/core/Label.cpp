#include "Label.h"

#include "LabelPrivate.h"

CUKE_BEGIN_NAMESPACE(widget)
CUKE_Q_PROPERTY_IMPL(Label, QColor, TextColor)

Label::Label(QWidget *parent)
    : ContextMixin(parent),
      d_ptr(new LabelPrivate(this)) {
    setAttribute(Qt::WA_TranslucentBackground);
}

Label::Label(const QString &text, QWidget *parent)
    : Label(parent) {
    setText(text);
}

Label::Label(const QString &text, const QColor &color, QWidget *parent)
    : Label(parent) {
    setText(text);
    _pTextColor = color;
}

Label::~Label() = default;

void Label::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    if (_pTextColor.isValid())
        p.setPen(_pTextColor);
    else
        p.setPen(pThemeColor(_themeMode, Text));

    p.drawText(rect(), alignment(), text());
}

CUKE_END_NAMESPACE(widget)
