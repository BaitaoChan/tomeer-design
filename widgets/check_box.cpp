#include "icon.h"
#include "theme.h"
#include "check_box.h"
#include "check_box_private.h"
#include "check_box_style.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(CheckBox, int, BorderRadius)
TOMEER_Q_PROPERTY_IMPL(CheckBox, ThemeType::ThemeMode, ThemeMode)
CheckBox::CheckBox(QWidget *parent)
    : QCheckBox(parent),
      d_ptr(new CheckBoxPrivate(this)) {
    setBorderRadius(4);
    setStyle(new CheckBoxStyle(style()));
    setIconSize(QSize(QFontMetrics(font()).height(), QFontMetrics(font()).height()));
    setMinimumSize(iconSize());
    connect(this, &CheckBox::pBorderRadiusChanged, this, QOverload<>::of(&CheckBox::update));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &CheckBox::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

CheckBox::CheckBox(const QString &text, QWidget *parent)
    : CheckBox(parent) {
    setText(text);
}

CheckBox::~CheckBox() = default;

void CheckBox::setIcon(IconType::Icon pIcon) {
    if (_pIcon != pIcon) {
        _pIcon = pIcon;
        pIconChanged();
        setIcon(TOMEER_ICON->getIcon(_pIcon));
    }
}

IconType::Icon CheckBox::getIcon() const {
    return _pIcon;
}

bool CheckBox::hitButton(const QPoint &pos) const {
    return rect().contains(pos);
}

void CheckBox::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(CheckBox);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END
