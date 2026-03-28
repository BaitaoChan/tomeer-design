#include "CukeTheme.h"
#include "CukeThemePrivate.h"
#include <QVariant>

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_SINGLETON_IMPL(CukeTheme)
CukeTheme::CukeTheme(QObject *parent)
    : QObject(parent),
      d_ptr(new CukeThemePrivate(this)) {
    Q_D(CukeTheme);
    d->_themeMode = CukeThemeType::Dark;

    initThemeColor();
}

CukeTheme::~CukeTheme() = default;

void CukeTheme::setThemeMode(CukeThemeType::ThemeMode Mode) {
    Q_D(CukeTheme);
    d->_themeMode = Mode;
    emit themeModeChanged(d->_themeMode);
}

CukeThemeType::ThemeMode CukeTheme::getThemeMode() {
    Q_D(CukeTheme);
    return d->_themeMode;
}

void CukeTheme::addThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color, QColor newColor) {
    Q_D(CukeTheme);
    if (Mode == CukeThemeType::Light) {
        d->_lightThemeColorList[Color] = newColor;
    } else if (Mode == CukeThemeType::Dark) {
        d->_darkThemeColorList[Color] = newColor;
    }
}

const QColor &CukeTheme::getThemeColor(CukeThemeType::ThemeMode Mode, CukeThemeType::ThemeColor Color) {
    Q_D(CukeTheme);
    if (Mode == CukeThemeType::Light) {
        return d->_lightThemeColorList[Color];
    } else if (Mode == CukeThemeType::Dark) {
        return d->_darkThemeColorList[Color];
    }
    return QColor();
}

void CukeTheme::initThemeColor() {
    Q_D(CukeTheme);
    // 透明
    d->_lightThemeColorList[CukeThemeType::Transparent] = QColor(255, 255, 255, 0);
    d->_darkThemeColorList[CukeThemeType::Transparent] = QColor(0, 0, 0, 0);

    d->_lightThemeColorList[CukeThemeType::Default] = QColor(160, 160, 160);
    d->_darkThemeColorList[CukeThemeType::Default] = QColor(82, 82, 82);
    d->_lightThemeColorList[CukeThemeType::Hover] = QColor(240, 240, 240);
    d->_darkThemeColorList[CukeThemeType::Hover] = QColor(52, 52, 52);
    d->_lightThemeColorList[CukeThemeType::Press] = QColor(230, 230, 230);
    d->_darkThemeColorList[CukeThemeType::Press] = QColor(32, 32, 32);
    d->_lightThemeColorList[CukeThemeType::Check] = QColor(0, 103, 192);
    d->_darkThemeColorList[CukeThemeType::Check] = QColor(0, 103, 192);
    d->_lightThemeColorList[CukeThemeType::Text] = QColor(0, 0, 0);
    d->_darkThemeColorList[CukeThemeType::Text] = QColor(255, 255, 255);
    d->_lightThemeColorList[CukeThemeType::Border] = QColor(128, 128, 128);
    d->_darkThemeColorList[CukeThemeType::Border] = QColor(53, 53, 53);
    d->_lightThemeColorList[CukeThemeType::Error] = QColor(220, 53, 69);
    d->_darkThemeColorList[CukeThemeType::Error] = QColor(220, 53, 69);

    // 窗体
    d->_lightThemeColorList[CukeThemeType::Window] = QColor(252, 252, 252);
    d->_darkThemeColorList[CukeThemeType::Window] = QColor(32, 32, 32);

    // 不使能
    d->_lightThemeColorList[CukeThemeType::Disable] = QColor(0xF5, 0xF5, 0xF5, 60);
    d->_darkThemeColorList[CukeThemeType::Disable] = QColor(0, 0, 0, 60);
    d->_lightThemeColorList[CukeThemeType::TextDisable] = QColor(0xB6, 0xB6, 0xB6);
    d->_darkThemeColorList[CukeThemeType::TextDisable] = QColor(0xA7, 0xA7, 0xA7);

    // 透明
    d->_lightThemeColorList[CukeThemeType::DefaultAlpha] = QColor(160, 160, 160, 32);
    d->_darkThemeColorList[CukeThemeType::DefaultAlpha] = QColor(52, 52, 52, 32);
    d->_lightThemeColorList[CukeThemeType::HoverAlpha] = QColor(255, 255, 255, 128);
    d->_darkThemeColorList[CukeThemeType::HoverAlpha] = QColor(52, 52, 52, 128);
    d->_lightThemeColorList[CukeThemeType::PressAlpha] = QColor(255, 255, 255, 200);
    d->_darkThemeColorList[CukeThemeType::PressAlpha] = QColor(52, 52, 52, 200);
    d->_lightThemeColorList[CukeThemeType::CheckAlpha] = QColor(0, 103, 192, 170);
    d->_darkThemeColorList[CukeThemeType::CheckAlpha] = QColor(0, 103, 192, 170);
    d->_lightThemeColorList[CukeThemeType::TextAlpha] = QColor(0, 0, 0, 200);
    d->_darkThemeColorList[CukeThemeType::TextAlpha] = QColor(255, 255, 255, 200);
    d->_lightThemeColorList[CukeThemeType::BorderAlpha] = QColor(128, 128, 128, 120);
    d->_darkThemeColorList[CukeThemeType::BorderAlpha] = QColor(53, 53, 53, 120);

    // 窗体透明
    d->_lightThemeColorList[CukeThemeType::WindowAlpha] = QColor(252, 252, 252, 120);
    d->_darkThemeColorList[CukeThemeType::WindowAlpha] = QColor(0, 0, 0, 60);

    // 面板透明
    d->_lightThemeColorList[CukeThemeType::PanelAlpha] = QColor(252, 252, 252, 60);
    d->_darkThemeColorList[CukeThemeType::PanelAlpha] = QColor(0, 0, 0, 40);

    // 样式
    d->_lightThemeColorList[CukeThemeType::Pattern] = QColor(200, 200, 200);
    d->_darkThemeColorList[CukeThemeType::Pattern] = QColor(10, 10, 10);

    // 焦点样式
    d->_lightThemeColorList[CukeThemeType::FocusBorder] = QColor(0, 120, 215);
    d->_darkThemeColorList[CukeThemeType::FocusBorder] = QColor(0, 120, 215);

    // ToggleSwitch
    d->_lightThemeColorList[CukeThemeType::ToggleSwitchKnob] = QColor(225, 225, 225, 220);
    d->_darkThemeColorList[CukeThemeType::ToggleSwitchKnob] = QColor(60, 60, 60, 220);
    d->_lightThemeColorList[CukeThemeType::ToggleSwitchBorder] = QColor(200, 200, 200);
    d->_darkThemeColorList[CukeThemeType::ToggleSwitchBorder] = QColor(60, 60, 60);

    // Slider
    d->_lightThemeColorList[CukeThemeType::SliderHandleBorder] = QColor(200, 200, 200);
    d->_darkThemeColorList[CukeThemeType::SliderHandleBorder] = QColor(60, 60, 60);

    // ShinyText
    d->_lightThemeColorList[CukeThemeType::ShinyText] = QColor(157, 157, 157);
    d->_darkThemeColorList[CukeThemeType::ShinyText] = QColor(178, 178, 178);
    d->_lightThemeColorList[CukeThemeType::Shiny] = QColor(255, 255, 255, 200);
    d->_darkThemeColorList[CukeThemeType::Shiny] = QColor(255, 255, 255, 250);

    // Waveform
    d->_lightThemeColorList[CukeThemeType::WaveformLegendText] = QColor(0, 0, 0);
    d->_darkThemeColorList[CukeThemeType::WaveformLegendText] = QColor(255, 255, 255);
    d->_lightThemeColorList[CukeThemeType::WaveformLegendBorder] = QColor(0, 0, 0, 255);
    d->_darkThemeColorList[CukeThemeType::WaveformLegendBorder] = QColor(255, 255, 255, 255);
    d->_lightThemeColorList[CukeThemeType::WaveformX] = QColor(0, 0, 0);
    d->_darkThemeColorList[CukeThemeType::WaveformX] = QColor(255, 255, 255);
    d->_lightThemeColorList[CukeThemeType::WaveformGrid] = QColor(100, 100, 100, 100);
    d->_darkThemeColorList[CukeThemeType::WaveformGrid] = QColor(140, 140, 140, 100);

    // LoopRing
    d->_lightThemeColorList[CukeThemeType::LoopRing] = QColor(31, 155, 93);
    d->_darkThemeColorList[CukeThemeType::LoopRing] = QColor(31, 155, 93);
    d->_lightThemeColorList[CukeThemeType::LoopText] = QColor(31, 155, 93);
    d->_darkThemeColorList[CukeThemeType::LoopText] = QColor(31, 155, 93);

    // Status
    d->_lightThemeColorList[CukeThemeType::Normal] = Qt::darkGreen;
    d->_darkThemeColorList[CukeThemeType::Normal] = Qt::darkGreen;

    d->_lightThemeColorList[CukeThemeType::Warning] = Qt::darkYellow;
    d->_darkThemeColorList[CukeThemeType::Warning] = Qt::darkYellow;

    d->_lightThemeColorList[CukeThemeType::Error] = Qt::red;
    d->_darkThemeColorList[CukeThemeType::Error] = Qt::red;

    // TableView
    d->_lightThemeColorList[CukeThemeType::HeaderBg] = QColor(0, 0, 0, 40);
    d->_darkThemeColorList[CukeThemeType::HeaderBg] = QColor(0, 0, 0, 40);
    d->_lightThemeColorList[CukeThemeType::TableBg] = QColor(252, 252, 252, 60);
    d->_darkThemeColorList[CukeThemeType::TableBg] = QColor(0, 0, 0, 40);
    d->_lightThemeColorList[CukeThemeType::SelectedItem] = QColor(0, 0, 0, 10);
    d->_darkThemeColorList[CukeThemeType::SelectedItem] = QColor(0, 0, 0, 10);

    // ComboBox
    d->_lightThemeColorList[CukeThemeType::ComboBoxView] = QColor(222, 222, 222);
    d->_darkThemeColorList[CukeThemeType::ComboBoxView] = QColor(52, 52, 52);
    d->_lightThemeColorList[CukeThemeType::ComboBoxItem] = QColor(252, 252, 252);
    d->_darkThemeColorList[CukeThemeType::ComboBoxItem] = QColor(22, 22, 22);

    // ToolButton
    d->_lightThemeColorList[CukeThemeType::Dismiss] = QColor(232, 17, 35);
    d->_darkThemeColorList[CukeThemeType::Dismiss] = QColor(232, 17, 35);
}

CUKE_NAMESPACE_END(pub)