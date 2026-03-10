#include "Theme.h"
#include "ThemePrivate.h"
#include <QVariant>

CUKE_BEGIN_NAMESPACE(widget)
Theme::Theme(QObject *parent)
    : QObject(parent),
      d_ptr(new ThemePrivate(this)) {
    d_ptr->_themeMode = ThemeType::Dark;

    initThemeColor();
}

Theme::~Theme() = default;

Theme *Theme::instance() {
    static Theme instance;
    return &instance;
}

void Theme::setThemeMode(ThemeType::Mode Mode) {
    d_ptr->_themeMode = Mode;
    emit themeModeChanged(d_ptr->_themeMode);
}

ThemeType::Mode Theme::getThemeMode() const {
    return d_ptr->_themeMode;
}

void Theme::addThemeColor(ThemeType::Mode Mode, ThemeType::Color Color, QColor newColor) {
    if (Mode == ThemeType::Light) {
        d_ptr->_lightThemeColorList[Color] = newColor;
    } else if (Mode == ThemeType::Dark) {
        d_ptr->_darkThemeColorList[Color] = newColor;
    }
}

const QColor &Theme::getThemeColor(ThemeType::Mode Mode, ThemeType::Color Color) {
    if (Mode == ThemeType::Light) {
        return d_ptr->_lightThemeColorList[Color];
    } else if (Mode == ThemeType::Dark) {
        return d_ptr->_darkThemeColorList[Color];
    }
    return QColor();
}

void Theme::initThemeColor() {
    // 透明
    d_ptr->_lightThemeColorList[ThemeType::Transparent] = QColor(255, 255, 255, 0);
    d_ptr->_darkThemeColorList[ThemeType::Transparent] = QColor(0, 0, 0, 0);

    d_ptr->_lightThemeColorList[ThemeType::Default] = QColor(160, 160, 160);
    d_ptr->_darkThemeColorList[ThemeType::Default] = QColor(82, 82, 82);
    d_ptr->_lightThemeColorList[ThemeType::Hover] = QColor(255, 255, 255);
    d_ptr->_darkThemeColorList[ThemeType::Hover] = QColor(52, 52, 52);
    d_ptr->_lightThemeColorList[ThemeType::Press] = QColor(230, 230, 230);
    d_ptr->_darkThemeColorList[ThemeType::Press] = QColor(32, 32, 32);
    d_ptr->_lightThemeColorList[ThemeType::Check] = QColor(0, 103, 192);
    d_ptr->_darkThemeColorList[ThemeType::Check] = QColor(0, 103, 192);
    d_ptr->_lightThemeColorList[ThemeType::Text] = QColor(0, 0, 0);
    d_ptr->_darkThemeColorList[ThemeType::Text] = QColor(255, 255, 255);
    d_ptr->_lightThemeColorList[ThemeType::Border] = QColor(128, 128, 128);
    d_ptr->_darkThemeColorList[ThemeType::Border] = QColor(53, 53, 53);
    d_ptr->_lightThemeColorList[ThemeType::Error] = QColor(220, 53, 69);
    d_ptr->_darkThemeColorList[ThemeType::Error] = QColor(220, 53, 69);

    // 窗体
    d_ptr->_lightThemeColorList[ThemeType::Window] = QColor(252, 252, 252);
    d_ptr->_darkThemeColorList[ThemeType::Window] = QColor(32, 32, 32);

    // 不使能
    d_ptr->_lightThemeColorList[ThemeType::Disable] = QColor(0xF5, 0xF5, 0xF5, 60);
    d_ptr->_darkThemeColorList[ThemeType::Disable] = QColor(0, 0, 0, 60);
    d_ptr->_lightThemeColorList[ThemeType::TextDisable] = QColor(0xB6, 0xB6, 0xB6);
    d_ptr->_darkThemeColorList[ThemeType::TextDisable] = QColor(0xA7, 0xA7, 0xA7);

    // 透明
    d_ptr->_lightThemeColorList[ThemeType::DefaultAlpha] = QColor(160, 160, 160, 32);
    d_ptr->_darkThemeColorList[ThemeType::DefaultAlpha] = QColor(52, 52, 52, 32);
    d_ptr->_lightThemeColorList[ThemeType::HoverAlpha] = QColor(255, 255, 255, 128);
    d_ptr->_darkThemeColorList[ThemeType::HoverAlpha] = QColor(52, 52, 52, 128);
    d_ptr->_lightThemeColorList[ThemeType::PressAlpha] = QColor(255, 255, 255, 200);
    d_ptr->_darkThemeColorList[ThemeType::PressAlpha] = QColor(52, 52, 52, 200);
    d_ptr->_lightThemeColorList[ThemeType::CheckAlpha] = QColor(0, 103, 192, 170);
    d_ptr->_darkThemeColorList[ThemeType::CheckAlpha] = QColor(0, 103, 192, 170);
    d_ptr->_lightThemeColorList[ThemeType::TextAlpha] = QColor(0, 0, 0, 200);
    d_ptr->_darkThemeColorList[ThemeType::TextAlpha] = QColor(255, 255, 255, 200);
    d_ptr->_lightThemeColorList[ThemeType::BorderAlpha] = QColor(128, 128, 128, 120);
    d_ptr->_darkThemeColorList[ThemeType::BorderAlpha] = QColor(53, 53, 53, 120);

    // 窗体透明
    d_ptr->_lightThemeColorList[ThemeType::WindowAlpha] = QColor(252, 252, 252, 120);
    d_ptr->_darkThemeColorList[ThemeType::WindowAlpha] = QColor(0, 0, 0, 60);

    // 面板透明
    d_ptr->_lightThemeColorList[ThemeType::PanelAlpha] = QColor(252, 252, 252, 60);
    d_ptr->_darkThemeColorList[ThemeType::PanelAlpha] = QColor(0, 0, 0, 40);

    // 样式
    d_ptr->_lightThemeColorList[ThemeType::Pattern] = QColor(200, 200, 200);
    d_ptr->_darkThemeColorList[ThemeType::Pattern] = QColor(10, 10, 10);

    // 焦点样式
    d_ptr->_lightThemeColorList[ThemeType::FocusBorder] = QColor(0, 120, 215);
    d_ptr->_darkThemeColorList[ThemeType::FocusBorder] = QColor(0, 120, 215);

    // ToggleSwitch
    d_ptr->_lightThemeColorList[ThemeType::ToggleSwitchKnob] = QColor(225, 225, 225, 220);
    d_ptr->_darkThemeColorList[ThemeType::ToggleSwitchKnob] = QColor(60, 60, 60, 220);
    d_ptr->_lightThemeColorList[ThemeType::ToggleSwitchBorder] = QColor(200, 200, 200);
    d_ptr->_darkThemeColorList[ThemeType::ToggleSwitchBorder] = QColor(60, 60, 60);

    // Slider
    d_ptr->_lightThemeColorList[ThemeType::SliderHandleBorder] = QColor(200, 200, 200);
    d_ptr->_darkThemeColorList[ThemeType::SliderHandleBorder] = QColor(60, 60, 60);

    // ShinyText
    d_ptr->_lightThemeColorList[ThemeType::ShinyText] = QColor(157, 157, 157);
    d_ptr->_darkThemeColorList[ThemeType::ShinyText] = QColor(178, 178, 178);
    d_ptr->_lightThemeColorList[ThemeType::Shiny] = QColor(255, 255, 255, 200);
    d_ptr->_darkThemeColorList[ThemeType::Shiny] = QColor(255, 255, 255, 250);

    // Waveform
    d_ptr->_lightThemeColorList[ThemeType::WaveformLegendText] = QColor(0, 0, 0);
    d_ptr->_darkThemeColorList[ThemeType::WaveformLegendText] = QColor(255, 255, 255);
    d_ptr->_lightThemeColorList[ThemeType::WaveformLegendBorder] = QColor(0, 0, 0, 255);
    d_ptr->_darkThemeColorList[ThemeType::WaveformLegendBorder] = QColor(255, 255, 255, 255);
    d_ptr->_lightThemeColorList[ThemeType::WaveformX] = QColor(0, 0, 0);
    d_ptr->_darkThemeColorList[ThemeType::WaveformX] = QColor(255, 255, 255);
    d_ptr->_lightThemeColorList[ThemeType::WaveformGrid] = QColor(100, 100, 100, 100);
    d_ptr->_darkThemeColorList[ThemeType::WaveformGrid] = QColor(140, 140, 140, 100);

    // LoopRing
    d_ptr->_lightThemeColorList[ThemeType::LoopRing] = QColor(31, 155, 93);
    d_ptr->_darkThemeColorList[ThemeType::LoopRing] = QColor(31, 155, 93);
    d_ptr->_lightThemeColorList[ThemeType::LoopText] = QColor(31, 155, 93);
    d_ptr->_darkThemeColorList[ThemeType::LoopText] = QColor(31, 155, 93);

    // Status
    d_ptr->_lightThemeColorList[ThemeType::Normal] = Qt::darkGreen;
    d_ptr->_darkThemeColorList[ThemeType::Normal] = Qt::darkGreen;

    d_ptr->_lightThemeColorList[ThemeType::Warning] = Qt::darkYellow;
    d_ptr->_darkThemeColorList[ThemeType::Warning] = Qt::darkYellow;

    d_ptr->_lightThemeColorList[ThemeType::Error] = Qt::red;
    d_ptr->_darkThemeColorList[ThemeType::Error] = Qt::red;

    // TableView
    d_ptr->_lightThemeColorList[ThemeType::HeaderBg] = QColor(0, 0, 0, 40);
    d_ptr->_darkThemeColorList[ThemeType::HeaderBg] = QColor(0, 0, 0, 40);
    d_ptr->_lightThemeColorList[ThemeType::TableBg] = QColor(252, 252, 252, 60);
    d_ptr->_darkThemeColorList[ThemeType::TableBg] = QColor(0, 0, 0, 40);
    d_ptr->_lightThemeColorList[ThemeType::SelectedItem] = QColor(0, 0, 0, 10);
    d_ptr->_darkThemeColorList[ThemeType::SelectedItem] = QColor(0, 0, 0, 10);

    // ComboBox
    d_ptr->_lightThemeColorList[ThemeType::ComboBoxView] = QColor(222, 222, 222);
    d_ptr->_darkThemeColorList[ThemeType::ComboBoxView] = QColor(52, 52, 52);
    d_ptr->_lightThemeColorList[ThemeType::ComboBoxItem] = QColor(252, 252, 252);
    d_ptr->_darkThemeColorList[ThemeType::ComboBoxItem] = QColor(22, 22, 22);
}

CUKE_END_NAMESPACE(widget)