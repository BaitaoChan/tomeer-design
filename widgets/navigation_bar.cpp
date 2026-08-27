#include "navigation_bar.h"

#include <QStyleOption>
#include <QStylePainter>
#include <QVBoxLayout>

#include "navigation_bar_item_delegate.h"
#include "navigation_bar_private.h"
#include "navigation_bar_style.h"
#include "navigation_bar_view.h"
#include "navigation_bar_view_style.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_PROPERTY_IMPL(NavigationBar, ThemeType::ThemeMode, ThemeMode)
NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent),
      d_ptr(new NavigationBarPrivate(this)) {
    Q_D(NavigationBar);

    setStyle(new NavigationBarStyle(style()));

    d->_view = new NavigationBarView(this);
    d->_view->setStyle(new NavigationBarViewStyle(d->_view->style()));
    d->_view->setItemDelegate(new NavigationBarItemDelegate(d->_view));

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(d->_view);

    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &NavigationBar::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

NavigationBar::~NavigationBar() = default;

void NavigationBar::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event)

    QStyleOption option;
    option.initFrom(this);

    QStylePainter painter(this);
    painter.drawPrimitive(QStyle::PE_Widget, option);
}

void NavigationBar::onThemeChanged(ThemeType::ThemeMode mode) {
    Q_D(NavigationBar);
    setThemeMode(mode);
    update();
}
TOMEER_NAMESPACE_END