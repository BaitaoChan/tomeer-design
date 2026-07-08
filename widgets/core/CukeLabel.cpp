#include "CukeLabel.h"

#include "CukeLabelPrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(Label, QColor, TextColor)
CUKE_Q_PROPERTY_IMPL(Label, ThemeType::ThemeMode, ThemeMode)
Label::Label(QWidget *parent)
    : QLabel(parent),
      d_ptr(new LabelPrivate(this)) {
    setAttribute(Qt::WA_TranslucentBackground);
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &Label::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
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
    Q_D(Label);
    QPainter p(this);
    p.setRenderHint(QPainter::TextAntialiasing, true);
    if (_pTextColor.isValid())
        p.setPen(_pTextColor);
    else
        p.setPen(CUKE_THEME->getThemeColor(ThemeType::Text));

    p.drawText(rect(), alignment(), text());
}

void Label::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(Label);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)
