#include "CukeComboBoxView.h"

CUKE_NAMESPACE_BEGIN(widget)
CukeComboBoxView::CukeComboBoxView(QWidget*parent)
    : CukeContextMixin(parent) {
    setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
    setSelectionMode(SingleSelection);
    setMouseTracking(true);
    setStyleSheet("background-color: transparent;");
    viewport()->setStyleSheet("background-color: transparent;");
    setViewportMargins(0, 0, 6, 6);
}

CukeComboBoxView::~CukeComboBoxView() = default;

int CukeComboBoxView::sizeHintForRow(const int row) const {
    Q_UNUSED(row);
    return 24;
}

void CukeComboBoxView::onThemeChanged(CukeThemeType::ThemeMode mode) {
    CukeContextMixin::onThemeChanged(mode);
    // 设置文字颜色
    QPalette pal = palette();
    pal.setColor(QPalette::Text, pThemeColor(_themeMode, Text));
    setPalette(pal);
}

CUKE_NAMESPACE_END(widget)