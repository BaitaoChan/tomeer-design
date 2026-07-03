#include <QStyleOption>
#include <QPainter>

#include "CukeToolBar.h"
#include "CukeToolBarStyle.h"
#include "CukeToolBarPrivate.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_PROPERTY_IMPL(CukeToolBar, CukeThemeType::ThemeMode, ThemeMode)
CukeToolBar::CukeToolBar(QWidget *parent)
    : QToolBar(parent),
      d_ptr(new CukeToolBarPrivate(this)) {
    Q_D(CukeToolBar);
    setStyle(new CukeToolBarStyle(style()));
    setAttribute(Qt::WA_TranslucentBackground);
    setOrientation(Qt::Horizontal);
    setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    // 文字图标高度一致
    setIconSize(QSize(QFontMetrics(font()).height(), QFontMetrics(font()).height()));
    connect(CUKE_THEME, &CukeTheme::themeModeChanged, this, &CukeToolBar::onThemeChanged);
    connect(CUKE_THEME, &CukeTheme::themeColorChanged, this, QOverload<>::of(&QWidget::update));
}

CukeToolBar::~CukeToolBar() = default;

void CukeToolBar::paintEvent(QPaintEvent *event) {
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

void CukeToolBar::onThemeChanged(CukeThemeType::ThemeMode mode) {
    Q_D(CukeToolBar);
    setThemeMode(mode);
    update();
}

CUKE_NAMESPACE_END(pub)