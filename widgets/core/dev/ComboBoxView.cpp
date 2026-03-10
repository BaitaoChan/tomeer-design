#include "ComboBoxView.h"

CUKE_BEGIN_NAMESPACE(widget)
ComboBoxView::ComboBoxView(QWidget*parent)
    : ContextMixin(parent) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setSelectionMode(SingleSelection);
    setMouseTracking(true);
    setStyleSheet("background-color: transparent;");
    viewport()->setStyleSheet("background-color: transparent;");
    setViewportMargins(0, 0, 6, 6);
}

ComboBoxView::~ComboBoxView() = default;

int ComboBoxView::sizeHintForRow(const int row) const {
    Q_UNUSED(row);
    return 24;
}

void ComboBoxView::onThemeChanged(ThemeType::Mode mode) {
    ContextMixin::onThemeChanged(mode);
    // 设置文字颜色
    QPalette pal = palette();
    pal.setColor(QPalette::Text, pThemeColor(_themeMode, Text));
    setPalette(pal);
}

CUKE_END_NAMESPACE(widget)