#ifndef DEF_H
#define DEF_H

#include <QObject>
#include <QMetaType>
#include "Property.h"

// 宏开始：声明一个带 Q_GADGET 的类
#define CUKE_DEF_BEGIN(CLASS)                               \
class CUKE_EXPORT CLASS : public QObject {                  \
Q_GADGET                                                    \
public:

// 宏结束：关闭类定义
#define CUKE_DEF_END(CLASS)                                 \
};

CUKE_DEF_BEGIN(ThemeType)
enum Mode {
    Light = 0x0000,
    Dark = 0x0001,
};

Q_ENUM(Mode)

enum Color {

    Transparent,

    Default,
    Hover,
    Press,
    Check,
    Border,

    Window,

    DefaultAlpha,
    HoverAlpha,
    PressAlpha,
    CheckAlpha,
    TextAlpha,
    BorderAlpha,

    WindowAlpha,
    PanelAlpha,

    Disable,
    TextDisable,

    Text,
    Pattern,

    FocusBorder,
    FocusPattern,

    ToggleSwitchKnob,
    ToggleSwitchBorder,

    SliderHandleBorder,

    ShinyText,
    Shiny,

    WaveformLegendText,
    WaveformLegendBorder,
    WaveformX,
    WaveformGrid,

    LoopRing,
    LoopText,

    HeaderBg,
    TableBg,
    SelectedItem,

    Normal,
    Warning,
    Error,

    ComboBoxView,
    ComboBoxItem,

};
Q_ENUM(Color)

CUKE_DEF_END(ThemeType)

#endif // DEF_H
