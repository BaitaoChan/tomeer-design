#include "CukeLabel.h"

#include "CukeLabelPrivate.h"

CUKE_NAMESPACE_BEGIN(widget)
CUKE_Q_PROPERTY_IMPL(CukeLabel, QColor, TextColor)

CukeLabel::CukeLabel(QWidget *parent)
    : CukeContextMixin(parent),
      d_ptr(new CukeLabelPrivate(this)) {
    setAttribute(Qt::WA_TranslucentBackground);
}

CukeLabel::CukeLabel(const QString &text, QWidget *parent)
    : CukeLabel(parent) {
    setText(text);
}

CukeLabel::CukeLabel(const QString &text, const QColor &color, QWidget *parent)
    : CukeLabel(parent) {
    setText(text);
    _pTextColor = color;
}

CukeLabel::~CukeLabel() = default;

void CukeLabel::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    if (_pTextColor.isValid())
        p.setPen(_pTextColor);
    else
        p.setPen(pThemeColor(_themeMode, Text));

    p.drawText(rect(), alignment(), text());
}

CUKE_NAMESPACE_END(widget)
