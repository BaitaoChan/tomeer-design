#include <QPropertyAnimation>
#include <QGuiApplication>
#include <QStyleHints>

#include "CukeTheme.h"
#include "CukeThemePrivate.h"

CUKE_NAMESPACE_BEGIN(pub)
namespace {
    struct ThemeColor {
        ThemeType::ThemeColor role;
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
        {ThemeType::Transparent, QColor(255, 255, 255, 0), QColor(0, 0, 0, 0)},

        // Basic
        {ThemeType::Default, QColor(160, 160, 160), QColor(82, 82, 82)},
        {ThemeType::Hover, QColor(240, 240, 240), QColor(52, 52, 52)},
        {ThemeType::Press, QColor(230, 230, 230), QColor(32, 32, 32)},
        {ThemeType::Check, QColor(0, 95, 184), QColor(0, 103, 192)},
        {ThemeType::Text, QColor(0, 0, 0), QColor(255, 255, 255)},
        {ThemeType::Border, QColor(200, 200, 200), QColor(10, 10, 10)},
        {ThemeType::Error, QColor(220, 53, 69), QColor(220, 53, 69)},

        // Window
        {ThemeType::Window, QColor(252, 252, 252), QColor(32, 32, 32)},
        {ThemeType::RubberBand, QColor(238, 238, 238), QColor(42, 42, 42)},

        // Disabled
        {ThemeType::Disable, QColor(245, 245, 245, 60), QColor(0, 0, 0, 60)},
        {ThemeType::TextDisable, QColor(80, 80, 80), QColor(167, 167, 167)},

        // Alpha
        {ThemeType::DefaultAlpha, QColor(160, 160, 160, 64), QColor(52, 52, 52, 32)},
        {ThemeType::HoverAlpha, QColor(232, 232, 232, 128), QColor(52, 52, 52, 128)},
        {ThemeType::PressAlpha, QColor(232, 232, 232, 200), QColor(52, 52, 52, 200)},
        {ThemeType::CheckAlpha, QColor(0, 95, 184, 230), QColor(0, 103, 192, 230)},
        {ThemeType::TextAlpha, QColor(0, 0, 0, 200), QColor(255, 255, 255, 200)},
        {ThemeType::BorderAlpha, QColor(200, 200, 200, 160), QColor(10, 10, 10, 60)},

        // Window Alpha
        {ThemeType::WindowAlpha, QColor(252, 252, 252, 140), QColor(0, 0, 0, 140)},

        // Mica
        {ThemeType::Mica, QColor(0, 103, 192, 10), QColor(0, 103, 192, 10)},

        // MicaAlt
        {ThemeType::MicaAlt, QColor(0, 103, 192, 10), QColor(0, 103, 192, 10)},

        // Acrylic
        {ThemeType::Acrylic, QColor(252, 252, 252, 140), QColor(0, 0, 0, 140)},

        // Panel Alpha
        {ThemeType::PanelAlpha, QColor(255, 255, 255, 20), QColor(255, 255, 255, 20)},

        // Pattern
        {ThemeType::Pattern, QColor(200, 200, 200, 160), QColor(10, 10, 10, 60)},

        // Separator
        {ThemeType::Separator, QColor(128, 128, 128), QColor(53, 53, 53)},

        // Focus
        {ThemeType::FocusBorder, QColor(0, 120, 215), QColor(0, 120, 215)},

        // ToggleSwitch
        {ThemeType::ToggleSwitchKnob, QColor(252, 252, 252), QColor(60, 60, 60)},
        {ThemeType::ToggleSwitchBorder, QColor(220, 220, 220), QColor(60, 60, 60)},

        // Slider
        {ThemeType::SliderHandleBorder, QColor(200, 200, 200), QColor(60, 60, 60)},

        // ScrollBar
        {ThemeType::ScrollBarHandle, QColor(0, 0, 0, 80), QColor(255, 255, 255, 72)},
        {ThemeType::ScrollBarHandleHover, QColor(0, 0, 0, 120), QColor(255, 255, 255, 112)},

        // Waveform
        {ThemeType::WaveformLegendText, QColor(0, 0, 0), QColor(255, 255, 255)},
        {ThemeType::WaveformLegendBorder, QColor(0, 0, 0, 255), QColor(255, 255, 255, 255)},
        {ThemeType::WaveformX, QColor(0, 0, 0), QColor(255, 255, 255)},
        {ThemeType::WaveformGrid, QColor(100, 100, 100, 100), QColor(140, 140, 140, 100)},

        // Status
        {ThemeType::Normal, Qt::darkGreen, Qt::darkGreen},
        {ThemeType::Warning, Qt::darkYellow, Qt::darkYellow},

        // TableView
        {ThemeType::HeaderBg, QColor(0, 0, 0, 40), QColor(0, 0, 0, 40)},
        {ThemeType::TableBg, QColor(252, 252, 252, 60), QColor(0, 0, 0, 40)},
        {ThemeType::SelectedItem, QColor(0, 0, 0, 10), QColor(0, 0, 0, 10)},

        // LineEdit
        {ThemeType::LineEdit, QColor(252, 252, 252), QColor(42, 42, 42)},

        // ComboBox
        {ThemeType::ComboBox, QColor(252, 252, 252), QColor(42, 42, 42)},
        {ThemeType::ComboBoxHover, QColor(248, 248, 248), QColor(48, 48, 48)},
        {ThemeType::ComboBoxView, QColor(242, 242, 242), QColor(42, 42, 42)},
        {ThemeType::ComboBoxItem, QColor(252, 252, 252), QColor(22, 22, 22)},

        // AppBarButton
        {ThemeType::Dismiss, QColor(232, 17, 35), QColor(232, 17, 35)},

        // ToolBar
        {ThemeType::ToolBarHandle, QColor(0, 95, 184), QColor(0, 103, 192)},
        {ThemeType::ToolBarBorder, QColor(98, 238, 147), QColor(98, 238, 147)},
        {ThemeType::ToolBarBg, QColor(245, 245, 245), QColor(42, 42, 42)},
    };
}

CUKE_Q_SINGLETON_IMPL(Theme)
Theme::Theme(QObject *parent)
    : QObject(parent),
      d_ptr(new ThemePrivate(this)) {
    Q_D(Theme);

    d->_colorAnimation = new QPropertyAnimation(d, "_pColorFactor", this);
    d->_colorAnimation->setDuration(250);
    d->_colorAnimation->setEasingCurve(QEasingCurve::InOutSine);

    initThemeColor();
    connect(d, &ThemePrivate::pColorFactorChanged, this, &Theme::themeColorChanged);
    connect(QGuiApplication::styleHints(), &QStyleHints::colorSchemeChanged, this, &Theme::onColorSchemeChanged);
}

Theme::~Theme() = default;

void Theme::setThemeMode(ThemeType::ThemeMode mode) {
    Q_D(Theme);
    // 将模式标记回 System
    if (mode == ThemeType::System && d->_colorAnimation->state() == QAbstractAnimation::Running) {
        d->_themeMode = mode;
        return;
    }
    d->_themeMode = mode;

    if (mode == ThemeType::System) {
        if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
            mode = ThemeType::Dark;
        else
            mode = ThemeType::Light;
    }

    const qreal tFactor = mode == ThemeType::Light ? 1.0 : 0.0;

    d->_colorAnimation->stop();
    // 切换缓冲
    d->_colorAnimation->setStartValue(d->getColorFactor());
    d->_colorAnimation->setEndValue(tFactor);
    d->_colorAnimation->start();

    emit themeModeChanged(d->_themeMode);
}

ThemeType::ThemeMode Theme::getThemeMode() {
    Q_D(Theme);
    return d->_themeMode;
}

void Theme::addThemeColor(ThemeType::ThemeMode mode, ThemeType::ThemeColor color, QColor newColor) {
    Q_D(Theme);
    if (mode == ThemeType::Light) {
        d->_lightThemeColorList[color] = newColor;
    } else if (mode == ThemeType::Dark) {
        d->_darkThemeColorList[color] = newColor;
    }
}

QColor Theme::getThemeColor(ThemeType::ThemeColor color) {
    Q_D(Theme);

    const QColor lightColor = d->_lightThemeColorList.value(color);
    const QColor darkColor = d->_darkThemeColorList.value(color);

    return mixColor(darkColor, lightColor, d->getColorFactor());
}

QColor Theme::getThemeColor(ThemeType::ThemeMode mode, ThemeType::ThemeColor color) {
    Q_D(Theme);

    if (mode == ThemeType::System) {
        if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
            mode = ThemeType::Dark;
        else
            mode = ThemeType::Light;
    }

    if (mode == ThemeType::Light)
        return d->_lightThemeColorList[color];
    if (mode == ThemeType::Dark)
        return d->_darkThemeColorList[color];
    return {};
}

void Theme::initThemeColor() {
    Q_D(Theme);

    d->_lightThemeColorList.clear();
    d->_darkThemeColorList.clear();

    for (const auto &color: themeColors) {
        d->_lightThemeColorList.insert(color.role, color.light);
        d->_darkThemeColorList.insert(color.role, color.dark);
    }
}

void Theme::onColorSchemeChanged(Qt::ColorScheme colorScheme) {
    Q_D(Theme);

    if (d->_themeMode != ThemeType::System)
        return;

    const qreal tFactor = colorScheme == Qt::ColorScheme::Dark ? 0.0 : 1.0;

    emit themeModeChanged(d->_themeMode);

    d->_colorAnimation->stop();
    d->_colorAnimation->setStartValue(d->getColorFactor());
    d->_colorAnimation->setEndValue(tFactor);
    d->_colorAnimation->start();
}

CUKE_NAMESPACE_END(pub)