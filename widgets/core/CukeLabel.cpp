#include "CukeLabel.h"

#include "CukeLabelPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeLabel, QColor, TextColor)
CUKE_Q_PROPERTY_IMPL(CukeLabel, CukeThemeType::ThemeMode, ThemeMode)
CukeLabel::CukeLabel(QWidget *parent)
    : QLabel(parent),
      d_ptr(new CukeLabelPrivate(this)) {
    setAttribute(Qt::WA_TranslucentBackground);
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeLabel::onThemeChanged);
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
    Q_D(CukeLabel);
    QPainter p(this);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    if (_pTextColor.isValid())
        p.setPen(_pTextColor);
    else
        p.setPen(CUKE_THEME->getThemeColor(getThemeMode(), CukeThemeType::Text));

    p.drawText(rect(), alignment(), text());
}

void CukeLabel::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeLabel);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)
