#include "CukeComboBoxView.h"
#include "CukeTheme.h"

CUKE_NAMESPACE_BEGIN(pub)
ComboBoxView::ComboBoxView(QWidget*parent)
    : QListView(parent) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setSelectionMode(SingleSelection);
    setMouseTracking(true);
    setStyleSheet("background-color: transparent;");
    viewport()->setStyleSheet("background-color: transparent;");
    setViewportMargins(0, 0, 6, 6);
    connect(CUKE_THEME, &Theme::themeModeChanged, this, &ComboBoxView::onThemeChanged);
    connect(CUKE_THEME, &Theme::themeColorChanged, viewport(), QOverload<>::of(&QWidget::update));
}

ComboBoxView::~ComboBoxView() = default;

int ComboBoxView::sizeHintForRow(const int row) const {
    Q_UNUSED(row);
    return 24;
}

void ComboBoxView::onThemeChanged(ThemeType::ThemeMode mode) {
    // 设置文字颜色
    QPalette pal = palette();
    pal.setColor(QPalette::Text, CUKE_THEME->getThemeColor(ThemeType::Text));
    setPalette(pal);
    update();
}

CUKE_NAMESPACE_END(pub)