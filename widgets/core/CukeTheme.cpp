#include "CukeTheme.h"
#include "CukeThemePrivate.h"
#include <QVariant>

CUKE_NAMESPACE_BEGIN(widget)
CUKE_Q_SINGLETON_IMPL(CukeTheme)
CukeTheme::CukeTheme(QObject *parent)
    : QObject(parent),
      d_ptr(new CukeThemePrivate(this)) {
    d_ptr->_themeMode = CukeThemeType::Dark;

    initThemeColor();
}

CukeTheme::~CukeTheme() = default;

void CukeTheme::setThemeMode(CukeThemeType::ThemeMode Mode) {
    d_ptr->_themeMode = Mode;
    emit themeModeChanged(d_ptr->_themeMode);
}

CukeThemeType::ThemeMode CukeTheme::getThemeMode() const {
    return d_ptr->_themeMode;
}

void CukeTheme::addThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color, QColor newColor) {
    if (Mode == CukeThemeType::Light) {
        d_ptr->_lightThemeColorList[Color] = newColor;
    } else if (Mode == CukeThemeType::Dark) {
        d_ptr->_darkThemeColorList[Color] = newColor;
    }
}

const QColor &CukeTheme::getThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color) {
    if (Mode == CukeThemeType::Light) {
        return d_ptr->_lightThemeColorList[Color];
    } else if (Mode == CukeThemeType::Dark) {
        return d_ptr->_darkThemeColorList[Color];
    }
    return QColor();
}

void CukeTheme::initThemeColor() {
    // 透明
    d_ptr->_lightThemeColorList[CukeThemeType::Transparent] = QColor(255, 255, 255, 0);
    d_ptr->_darkThemeColorList[CukeThemeType::Transparent] = QColor(0, 0, 0, 0);

    d_ptr->_lightThemeColorList[CukeThemeType::Default] = QColor(160, 160, 160);
    d_ptr->_darkThemeColorList[CukeThemeType::Default] = QColor(82, 82, 82);
    d_ptr->_lightThemeColorList[CukeThemeType::Hover] = QColor(255, 255, 255);
    d_ptr->_darkThemeColorList[CukeThemeType::Hover] = QColor(52, 52, 52);
    d_ptr->_lightThemeColorList[CukeThemeType::Press] = QColor(230, 230, 230);
    d_ptr->_darkThemeColorList[CukeThemeType::Press] = QColor(32, 32, 32);
    d_ptr->_lightThemeColorList[CukeThemeType::Check] = QColor(0, 103, 192);
    d_ptr->_darkThemeColorList[CukeThemeType::Check] = QColor(0, 103, 192);
    d_ptr->_lightThemeColorList[CukeThemeType::Text] = QColor(0, 0, 0);
    d_ptr->_darkThemeColorList[CukeThemeType::Text] = QColor(255, 255, 255);
    d_ptr->_lightThemeColorList[CukeThemeType::Border] = QColor(128, 128, 128);
    d_ptr->_darkThemeColorList[CukeThemeType::Border] = QColor(53, 53, 53);
    d_ptr->_lightThemeColorList[CukeThemeType::Error] = QColor(220, 53, 69);
    d_ptr->_darkThemeColorList[CukeThemeType::Error] = QColor(220, 53, 69);

    // 窗体
    d_ptr->_lightThemeColorList[CukeThemeType::Window] = QColor(252, 252, 252);
    d_ptr->_darkThemeColorList[CukeThemeType::Window] = QColor(32, 32, 32);

    // 不使能
    d_ptr->_lightThemeColorList[CukeThemeType::Disable] = QColor(0xF5, 0xF5, 0xF5, 60);
    d_ptr->_darkThemeColorList[CukeThemeType::Disable] = QColor(0, 0, 0, 60);
    d_ptr->_lightThemeColorList[CukeThemeType::TextDisable] = QColor(0xB6, 0xB6, 0xB6);
    d_ptr->_darkThemeColorList[CukeThemeType::TextDisable] = QColor(0xA7, 0xA7, 0xA7);

    // 透明
    d_ptr->_lightThemeColorList[CukeThemeType::DefaultAlpha] = QColor(160, 160, 160, 32);
    d_ptr->_darkThemeColorList[CukeThemeType::DefaultAlpha] = QColor(52, 52, 52, 32);
    d_ptr->_lightThemeColorList[CukeThemeType::HoverAlpha] = QColor(255, 255, 255, 128);
    d_ptr->_darkThemeColorList[CukeThemeType::HoverAlpha] = QColor(52, 52, 52, 128);
    d_ptr->_lightThemeColorList[CukeThemeType::PressAlpha] = QColor(255, 255, 255, 200);
    d_ptr->_darkThemeColorList[CukeThemeType::PressAlpha] = QColor(52, 52, 52, 200);
    d_ptr->_lightThemeColorList[CukeThemeType::CheckAlpha] = QColor(0, 103, 192, 170);
    d_ptr->_darkThemeColorList[CukeThemeType::CheckAlpha] = QColor(0, 103, 192, 170);
    d_ptr->_lightThemeColorList[CukeThemeType::TextAlpha] = QColor(0, 0, 0, 200);
    d_ptr->_darkThemeColorList[CukeThemeType::TextAlpha] = QColor(255, 255, 255, 200);
    d_ptr->_lightThemeColorList[CukeThemeType::BorderAlpha] = QColor(128, 128, 128, 120);
    d_ptr->_darkThemeColorList[CukeThemeType::BorderAlpha] = QColor(53, 53, 53, 120);

    // 窗体透明
    d_ptr->_lightThemeColorList[CukeThemeType::WindowAlpha] = QColor(252, 252, 252, 120);
    d_ptr->_darkThemeColorList[CukeThemeType::WindowAlpha] = QColor(0, 0, 0, 60);

    // 面板透明
    d_ptr->_lightThemeColorList[CukeThemeType::PanelAlpha] = QColor(252, 252, 252, 60);
    d_ptr->_darkThemeColorList[CukeThemeType::PanelAlpha] = QColor(0, 0, 0, 40);

    // 样式
    d_ptr->_lightThemeColorList[CukeThemeType::Pattern] = QColor(200, 200, 200);
    d_ptr->_darkThemeColorList[CukeThemeType::Pattern] = QColor(10, 10, 10);

    // 焦点样式
    d_ptr->_lightThemeColorList[CukeThemeType::FocusBorder] = QColor(0, 120, 215);
    d_ptr->_darkThemeColorList[CukeThemeType::FocusBorder] = QColor(0, 120, 215);

    // ToggleSwitch
    d_ptr->_lightThemeColorList[CukeThemeType::ToggleSwitchKnob] = QColor(225, 225, 225, 220);
    d_ptr->_darkThemeColorList[CukeThemeType::ToggleSwitchKnob] = QColor(60, 60, 60, 220);
    d_ptr->_lightThemeColorList[CukeThemeType::ToggleSwitchBorder] = QColor(200, 200, 200);
    d_ptr->_darkThemeColorList[CukeThemeType::ToggleSwitchBorder] = QColor(60, 60, 60);

    // Slider
    d_ptr->_lightThemeColorList[CukeThemeType::SliderHandleBorder] = QColor(200, 200, 200);
    d_ptr->_darkThemeColorList[CukeThemeType::SliderHandleBorder] = QColor(60, 60, 60);

    // ShinyText
    d_ptr->_lightThemeColorList[CukeThemeType::ShinyText] = QColor(157, 157, 157);
    d_ptr->_darkThemeColorList[CukeThemeType::ShinyText] = QColor(178, 178, 178);
    d_ptr->_lightThemeColorList[CukeThemeType::Shiny] = QColor(255, 255, 255, 200);
    d_ptr->_darkThemeColorList[CukeThemeType::Shiny] = QColor(255, 255, 255, 250);

    // Waveform
    d_ptr->_lightThemeColorList[CukeThemeType::WaveformLegendText] = QColor(0, 0, 0);
    d_ptr->_darkThemeColorList[CukeThemeType::WaveformLegendText] = QColor(255, 255, 255);
    d_ptr->_lightThemeColorList[CukeThemeType::WaveformLegendBorder] = QColor(0, 0, 0, 255);
    d_ptr->_darkThemeColorList[CukeThemeType::WaveformLegendBorder] = QColor(255, 255, 255, 255);
    d_ptr->_lightThemeColorList[CukeThemeType::WaveformX] = QColor(0, 0, 0);
    d_ptr->_darkThemeColorList[CukeThemeType::WaveformX] = QColor(255, 255, 255);
    d_ptr->_lightThemeColorList[CukeThemeType::WaveformGrid] = QColor(100, 100, 100, 100);
    d_ptr->_darkThemeColorList[CukeThemeType::WaveformGrid] = QColor(140, 140, 140, 100);

    // LoopRing
    d_ptr->_lightThemeColorList[CukeThemeType::LoopRing] = QColor(31, 155, 93);
    d_ptr->_darkThemeColorList[CukeThemeType::LoopRing] = QColor(31, 155, 93);
    d_ptr->_lightThemeColorList[CukeThemeType::LoopText] = QColor(31, 155, 93);
    d_ptr->_darkThemeColorList[CukeThemeType::LoopText] = QColor(31, 155, 93);

    // Status
    d_ptr->_lightThemeColorList[CukeThemeType::Normal] = Qt::darkGreen;
    d_ptr->_darkThemeColorList[CukeThemeType::Normal] = Qt::darkGreen;

    d_ptr->_lightThemeColorList[CukeThemeType::Warning] = Qt::darkYellow;
    d_ptr->_darkThemeColorList[CukeThemeType::Warning] = Qt::darkYellow;

    d_ptr->_lightThemeColorList[CukeThemeType::Error] = Qt::red;
    d_ptr->_darkThemeColorList[CukeThemeType::Error] = Qt::red;

    // TableView
    d_ptr->_lightThemeColorList[CukeThemeType::HeaderBg] = QColor(0, 0, 0, 40);
    d_ptr->_darkThemeColorList[CukeThemeType::HeaderBg] = QColor(0, 0, 0, 40);
    d_ptr->_lightThemeColorList[CukeThemeType::TableBg] = QColor(252, 252, 252, 60);
    d_ptr->_darkThemeColorList[CukeThemeType::TableBg] = QColor(0, 0, 0, 40);
    d_ptr->_lightThemeColorList[CukeThemeType::SelectedItem] = QColor(0, 0, 0, 10);
    d_ptr->_darkThemeColorList[CukeThemeType::SelectedItem] = QColor(0, 0, 0, 10);

    // ComboBox
    d_ptr->_lightThemeColorList[CukeThemeType::ComboBoxView] = QColor(222, 222, 222);
    d_ptr->_darkThemeColorList[CukeThemeType::ComboBoxView] = QColor(52, 52, 52);
    d_ptr->_lightThemeColorList[CukeThemeType::ComboBoxItem] = QColor(252, 252, 252);
    d_ptr->_darkThemeColorList[CukeThemeType::ComboBoxItem] = QColor(22, 22, 22);
}

CUKE_NAMESPACE_END(widget)