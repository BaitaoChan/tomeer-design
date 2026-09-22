#include "ControlsPage.h"

#include <QVBoxLayout>

#include "check_box.h"
#include "combo_box.h"
#include "line_edit.h"
#include "plain_text_edit.h"
#include "push_button.h"
#include "settings_card.h"
#include "slider.h"
#include "toggle_button.h"
#include "toggle_switch.h"

ControlsPage::ControlsPage(QWidget *parent)
    : ScrollArea(parent) {
    setWidgetResizable(true);

    auto content = new QWidget(this);
    auto layout = new QVBoxLayout(content);
    layout->setContentsMargins(24, 20, 24, 20);
    layout->setSpacing(8);

    constexpr int controlHeight = 32;
    constexpr int borderRadius = 6;

    auto pushButton = new PushButton(IconType::Calendar3Day, "Button");
    pushButton->setFixedSize(100, controlHeight);
    pushButton->setBorderRadius(borderRadius);
    layout->addWidget(new SettingsCard("PushButton", pushButton, content));

    auto toggleButton = new ToggleButton(IconType::CalendarLtr, "Button");
    toggleButton->setFixedSize(100, controlHeight);
    toggleButton->setBorderRadius(borderRadius);
    layout->addWidget(new SettingsCard("ToggleButton", toggleButton, content));

    auto checkBox = new CheckBox;
    checkBox->setChecked(true);
    layout->addWidget(new SettingsCard("CheckBox", checkBox, content));

    auto lineEdit = new LineEdit;
    lineEdit->setPlaceholderText("Enter text");
    lineEdit->setFixedSize(100, controlHeight);
    lineEdit->setBorderRadius(borderRadius);
    layout->addWidget(new SettingsCard("LineEdit", lineEdit, content));

    auto plainTextEdit = new PlainTextEdit;
    plainTextEdit->setPlainText(QStringLiteral("但愿现实中的金阁比我想像中的金阁会显出更清晰的美。\n\n——三岛由纪夫《金阁寺》"));
    plainTextEdit->setFixedSize(360, 100);
    plainTextEdit->setBorderRadius(borderRadius);
    layout->addWidget(new SettingsCard("PlainTextEdit", plainTextEdit, content));

    auto comboBox = new ComboBox;
    comboBox->addItems({"One", "Two", "Three"});
    comboBox->setFixedSize(100, controlHeight);
    comboBox->setBorderRadius(borderRadius);
    layout->addWidget(new SettingsCard("ComboBox", comboBox, content));

    auto slider = new Slider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(50);
    slider->setFixedSize(200, controlHeight);
    layout->addWidget(new SettingsCard("Slider", slider, content));

    auto toggleSwitch = new ToggleSwitch;
    toggleSwitch->setIsToggled(true);
    layout->addWidget(new SettingsCard("ToggleSwitch", toggleSwitch, content));
    layout->addStretch();

    setWidget(content);
}

ControlsPage::~ControlsPage() = default;
