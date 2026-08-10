#include "combo_box_view.h"
#include "theme.h"

TOMEER_NAMESPACE_BEGIN()
ComboBoxView::ComboBoxView(QWidget*parent)
    : QListView(parent) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setSelectionMode(SingleSelection);
    setMouseTracking(true);
    setStyleSheet("background-color: transparent;");
    viewport()->setStyleSheet("background-color: transparent;");
    setViewportMargins(0, 0, 6, 6);
    connect(TOMEER_THEME, &Theme::themeModeChanged, this, &ComboBoxView::onThemeChanged);
    connect(TOMEER_THEME, &Theme::themeColorChanged, viewport(), QOverload<>::of(&QWidget::update));
}

ComboBoxView::~ComboBoxView() = default;

int ComboBoxView::sizeHintForRow(const int row) const {
    Q_UNUSED(row);
    return 24;
}

void ComboBoxView::onThemeChanged(ThemeType::ThemeMode mode) {
    // 设置文字颜色
    QPalette pal = palette();
    pal.setColor(QPalette::Text, TOMEER_THEME->getThemeColor(ThemeType::Text));
    setPalette(pal);
    update();
}

TOMEER_NAMESPACE_END