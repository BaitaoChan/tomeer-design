#include "label.h"

#include "label_private.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(Label, QColor, TextColor)
TOMEER_Q_PROPERTY_IMPL(Label, ThemeType::ThemeMode, ThemeMode)
Label::Label(QWidget *parent)
    : QLabel(parent),
      d_ptr(new LabelPrivate(this)) {
    setAttribute(Qt::WA_TranslucentBackground);
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &Label::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
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
        p.setPen(TOMEER_THEME->getThemeColor(ThemeType::Text));

    p.drawText(rect(), alignment(), text());
}

void Label::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(Label);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END