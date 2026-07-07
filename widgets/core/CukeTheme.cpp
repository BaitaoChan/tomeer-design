#include "CukeTheme.h"
#include "CukeThemePrivate.h"
#include <QPropertyAnimation>

CUKE_NAMESPACE_BEGIN(pub)
namespace {
    struct ThemeColor {
        CukeThemeType::ThemeColor role;
        QColor light;
        QColor dark;
    };

    QColor mixColor(const QColor &dark, const QColor &light, qreal factor) {
        factor = qBound<qreal>(0.0, factor, 1.0);

        return {
            qRound(dark.red() + (light.red() - dark.red()) * factor),
            qRound(dark.green() + (light.green() - dark.green()) * factor),
            qRound(dark.blue() + (light.blue() - dark.blue()) * factor),
            qRound(dark.alpha() + (light.alpha() - dark.alpha()) * factor)
        };
    }

    const ThemeColor themeColors[] = {
        // Transparent
        {CukeThemeType::Transparent, QColor(255, 255, 255, 0), QColor(0, 0, 0, 0)},

        // Basic
        {CukeThemeType::Default, QColor(160, 160, 160), QColor(82, 82, 82)},
        {CukeThemeType::Hover, QColor(240, 240, 240), QColor(52, 52, 52)},
        {CukeThemeType::Press, QColor(230, 230, 230), QColor(32, 32, 32)},
        {CukeThemeType::Check, QColor(0, 103, 192), QColor(0, 103, 192)},
        {CukeThemeType::Text, QColor(0, 0, 0), QColor(255, 255, 255)},
        {CukeThemeType::Border, QColor(128, 128, 128), QColor(53, 53, 53)},
        {CukeThemeType::Error, QColor(220, 53, 69), QColor(220, 53, 69)},

        // Window
        {CukeThemeType::Window, QColor(252, 252, 252), QColor(32, 32, 32)},
        {CukeThemeType::RubberBand, QColor(238, 238, 238), QColor(42, 42, 42)},

        // Disabled
        {CukeThemeType::Disable, QColor(245, 245, 245, 60), QColor(0, 0, 0, 60)},
        {CukeThemeType::TextDisable, QColor(182, 182, 182), QColor(167, 167, 167)},

        // Alpha
        {CukeThemeType::DefaultAlpha, QColor(160, 160, 160, 64), QColor(52, 52, 52, 32)},
        {CukeThemeType::HoverAlpha, QColor(232, 232, 232, 128), QColor(52, 52, 52, 128)},
        {CukeThemeType::PressAlpha, QColor(232, 232, 232, 200), QColor(52, 52, 52, 200)},
        {CukeThemeType::CheckAlpha, QColor(0, 103, 192, 170), QColor(0, 103, 192, 170)},
        {CukeThemeType::TextAlpha, QColor(0, 0, 0, 200), QColor(255, 255, 255, 200)},
        {CukeThemeType::BorderAlpha, QColor(128, 128, 128, 120), QColor(53, 53, 53, 120)},

        // Window Alpha
        {CukeThemeType::WindowAlpha, QColor(252, 252, 252, 120), QColor(0, 0, 0, 60)},

        // Panel Alpha
        {CukeThemeType::PanelAlpha, QColor(252, 252, 252, 60), QColor(0, 0, 0, 40)},

        // Pattern
        {CukeThemeType::Pattern, QColor(200, 200, 200, 160), QColor(10, 10, 10, 60)},

        // Focus
        {CukeThemeType::FocusBorder, QColor(0, 120, 215), QColor(0, 120, 215)},

        // ToggleSwitch
        {CukeThemeType::ToggleSwitchKnob, QColor(252, 252, 252), QColor(60, 60, 60)},
        {CukeThemeType::ToggleSwitchBorder, QColor(220, 220, 220), QColor(60, 60, 60)},

        // Slider
        {CukeThemeType::SliderHandleBorder, QColor(200, 200, 200), QColor(60, 60, 60)},

        // Waveform
        {CukeThemeType::WaveformLegendText, QColor(0, 0, 0), QColor(255, 255, 255)},
        {CukeThemeType::WaveformLegendBorder, QColor(0, 0, 0, 255), QColor(255, 255, 255, 255)},
        {CukeThemeType::WaveformX, QColor(0, 0, 0), QColor(255, 255, 255)},
        {CukeThemeType::WaveformGrid, QColor(100, 100, 100, 100), QColor(140, 140, 140, 100)},

        // Status
        {CukeThemeType::Normal, Qt::darkGreen, Qt::darkGreen},
        {CukeThemeType::Warning, Qt::darkYellow, Qt::darkYellow},

        // TableView
        {CukeThemeType::HeaderBg, QColor(0, 0, 0, 40), QColor(0, 0, 0, 40)},
        {CukeThemeType::TableBg, QColor(252, 252, 252, 60), QColor(0, 0, 0, 40)},
        {CukeThemeType::SelectedItem, QColor(0, 0, 0, 10), QColor(0, 0, 0, 10)},

        // ComboBox
        {CukeThemeType::ComboBox, QColor(252, 252, 252), QColor(42, 42, 42)},
        {CukeThemeType::ComboBoxHover, QColor(248, 248, 248), QColor(48, 48, 48)},
        {CukeThemeType::ComboBoxView, QColor(242, 242, 242), QColor(42, 42, 42)},
        {CukeThemeType::ComboBoxItem, QColor(252, 252, 252), QColor(22, 22, 22)},

        // AppBarButton
        {CukeThemeType::Dismiss, QColor(232, 17, 35), QColor(232, 17, 35)},

        // ToolBar
        {CukeThemeType::ToolBarHandle, QColor(98, 238, 147), QColor(98, 238, 147)},
        {CukeThemeType::ToolBarBorder, QColor(98, 238, 147), QColor(98, 238, 147)},
        {CukeThemeType::ToolBarBg, QColor(245, 245, 245), QColor(42, 42, 42)},
    };
}

CUKE_Q_SINGLETON_IMPL(CukeTheme)
CukeTheme::CukeTheme(QObject *parent)
    : QObject(parent),
      d_ptr(new CukeThemePrivate(this)) {
    Q_D(CukeTheme);

    d->_colorAnimation = new QPropertyAnimation(d, "_pColorFactor", this);
    d->_colorAnimation->setDuration(250);
    d->_colorAnimation->setEasingCurve(QEasingCurve::InOutSine);

    initThemeColor();
    connect(d, &CukeThemePrivate::pColorFactorChanged, this, &CukeTheme::themeColorChanged);
}

CukeTheme::~CukeTheme() = default;

void CukeTheme::setThemeMode(CukeThemeType::ThemeMode mode) {
    Q_D(CukeTheme);
    d->_themeMode = mode;

    const qreal tFactor = mode == CukeThemeType::Light ? 1.0 : 0.0;

    d->_colorAnimation->stop();
    // 切换缓冲
    d->_colorAnimation->setStartValue(d->getColorFactor());
    d->_colorAnimation->setEndValue(tFactor);
    d->_colorAnimation->start();

    emit themeModeChanged(d->_themeMode);
}

CukeThemeType::ThemeMode CukeTheme::getThemeMode() {
    Q_D(CukeTheme);
    return d->_themeMode;
}

void CukeTheme::addThemeColor(CukeThemeType::ThemeMode mode, CukeThemeType::ThemeColor color, QColor newColor) {
    Q_D(CukeTheme);
    if (mode == CukeThemeType::Light) {
        d->_lightThemeColorList[color] = newColor;
    } else if (mode == CukeThemeType::Dark) {
        d->_darkThemeColorList[color] = newColor;
    }
}

QColor CukeTheme::getThemeColor(CukeThemeType::ThemeColor color) {
    Q_D(CukeTheme);

    const QColor lightColor = d->_lightThemeColorList.value(color);
    const QColor darkColor = d->_darkThemeColorList.value(color);

    return mixColor(darkColor, lightColor, d->getColorFactor());
}

QColor CukeTheme::getThemeColor(CukeThemeType::ThemeMode mode, CukeThemeType::ThemeColor color) {
    Q_D(CukeTheme);
    if (mode == CukeThemeType::Light) {
        return d->_lightThemeColorList[color];
    }
    if (mode == CukeThemeType::Dark) {
        return d->_darkThemeColorList[color];
    }
    return {};
}

void CukeTheme::initThemeColor() {
    Q_D(CukeTheme);

    d->_lightThemeColorList.clear();
    d->_darkThemeColorList.clear();

    for (const auto &color: themeColors) {
        d->_lightThemeColorList.insert(color.role, color.light);
        d->_darkThemeColorList.insert(color.role, color.dark);
    }
}

CUKE_NAMESPACE_END(pub)