#include <QStyleOption>
#include <QPainter>

#include "action.h"
#include "tool_bar.h"
#include "tool_bar_style.h"
#include "tool_button.h"
#include "tool_bar_private.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(ToolBar, ThemeType::ThemeMode, ThemeMode)
ToolBar::ToolBar(QWidget *parent)
    : QToolBar(parent),
      d_ptr(new ToolBarPrivate(this)) {
    Q_D(ToolBar);
    setStyle(new ToolBarStyle(style()));
    setAttribute(Qt::WA_TranslucentBackground);
    setOrientation(Qt::Horizontal);
    setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    // 文字图标高度一致
    setIconSize(QSize(QFontMetrics(font()).height(), QFontMetrics(font()).height()));
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &ToolBar::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

ToolBar::~ToolBar() = default;

Action *ToolBar::addAction(Action *action) {
    if (!action)
        return nullptr;

    const auto toolButton = new ToolButton(this);
    toolButton->setDefaultAction(action);
    addWidget(toolButton);

    return action;
}

void ToolBar::paintEvent(QPaintEvent *event) {
    if (isFloating()) {
        QPainter p(this);
        QStyleOptionToolBar opt;
        initStyleOption(&opt);
        // ToolBar 区域
        opt.rect = style()->subElementRect(QStyle::SE_ToolBarHandle, &opt, this);
        style()->drawControl(QStyle::CE_ToolBar, &opt, &p, this);
        style()->drawPrimitive(QStyle::PE_IndicatorToolBarHandle, &opt, &p, this);
        return;
    }
    QToolBar::paintEvent(event);
}

void ToolBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(ToolBar);
    setThemeMode(mode);
    update();
}

TOMEER_NAMESPACE_END