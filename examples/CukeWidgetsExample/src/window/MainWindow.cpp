#include "MainWindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>

#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>

#include <QMenu>
#include <QAction>
#include <QActionGroup>

#include <QFile>

#include "CukeIcon.h"
#include "CukeAction.h"
#include "CukeMenu.h"
#include "CukeAppBar.h"
#include "CukeMenuBar.h"
#include "CukeToolBar.h"
#include "CukeToolButton.h"
#include "CukeScrollArea.h"
#include "CukeSettingsCard.h"
#include "CukeLabel.h"
#include "CukeLineEdit.h"
#include "CukeComboBox.h"
#include "CukeSlider.h"
#include "CukeToggleSwitch.h"

MainWindow::MainWindow(QWidget *parent)
    : Window(parent) {
    // setWindowTitle("Widgets");
    setWindowIcon(QIcon(":/images/GreenSun.svg"));

    auto menuBar = new MenuBar(this);
    menuBar->addAction(new Action(IconType::Book, "文件"));
    menuBar->addAction(new QAction("编辑"));
    menuBar->addAction(new QAction("视图"));
    menuBar->addAction(new QAction("项目"));
    menuBar->addAction(new QAction("生成"));
    menuBar->addAction(new QAction("调试"));
    auto disabledMenuBarAction = new Action("拓展", menuBar);
    disabledMenuBarAction->setEnabled(false);
    menuBar->addAction(disabledMenuBarAction);
    appBar()->addCustomWidget(menuBar, AppBarType::LeftArea);
    setDisplayMode(WindowType::Mica);

    auto toolBar = new ToolBar(this);
    auto toolButton1 = new ToolButton(this);
    toolButton1->setText("开始");
    auto toolButton2 = new ToolButton(this);
    // toolButton2->setIcon(CUKE_ICON->getCukeIcon(IconType::CommentAdd, CUKE_THEME->getThemeColor(ThemeType::Text), 64));
    toolButton2->setIconType(IconType::BookCoins);
    auto toolButton3 = new ToolButton(this);
    toolButton3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton3->setText("统计");
    // toolButton3->setIcon(CUKE_ICON->getCukeIcon(IconType::Dismiss, CUKE_THEME->getThemeColor(ThemeType::Text), 64));
    toolButton3->setIconType(IconType::AppGeneric);
    auto menu3 = new Menu(this);
    menu3->addAction(new QAction("样例1"));
    auto disabledMenuAction = new QAction("样例2", menu3);
    disabledMenuAction->setEnabled(false);
    menu3->addAction(disabledMenuAction);
    menu3->addAction(new QAction("样例3"));

    auto sample4Action = new Action(IconType::CommentAdd, "样例4", menu3);
    sample4Action->setShortcut(QKeySequence("Ctrl+4"));
    sample4Action->setCheckable(true);
    sample4Action->setChecked(true);
    sample4Action->setToolTip("这是样例4，用于测试 Action");
    sample4Action->setStatusTip("触发样例4 Action");
    menu3->addAction(sample4Action);

    auto checkedMenuAction = new Action("无图标勾选", menu3);
    checkedMenuAction->setCheckable(true);
    checkedMenuAction->setChecked(true);
    menu3->addAction(checkedMenuAction);

    auto exclusiveGroup = new QActionGroup(menu3);
    exclusiveGroup->setExclusive(true);
    auto exclusiveAction1 = new Action("互斥项1", menu3);
    exclusiveAction1->setCheckable(true);
    exclusiveAction1->setChecked(true);
    exclusiveGroup->addAction(exclusiveAction1);
    menu3->addAction(exclusiveAction1);
    auto exclusiveAction2 = new Action("互斥项2", menu3);
    exclusiveAction2->setCheckable(true);
    exclusiveGroup->addAction(exclusiveAction2);
    menu3->addAction(exclusiveAction2);

    auto subMenu = new Menu("更多", menu3);
    subMenu->setIconType(IconType::Desktop);
    subMenu->addAction(new Action("子项1", subMenu));
    subMenu->addAction(new Action(IconType::BookCoins, "子项2", subMenu));
    subMenu->addSeparator();
    auto disabledSubMenuAction = new Action("禁用子项", subMenu);
    disabledSubMenuAction->setEnabled(false);
    subMenu->addAction(disabledSubMenuAction);
    auto checkedSubMenuAction = new Action("勾选子项", subMenu);
    checkedSubMenuAction->setCheckable(true);
    checkedSubMenuAction->setChecked(true);
    subMenu->addAction(checkedSubMenuAction);
    subMenu->addAction(new Action(IconType::Cloud, "图标子项", subMenu));
    auto *subAction = menu3->addCukeMenu(subMenu);
    subAction->setShortcut(QKeySequence("Ctrl+M"));

    toolButton3->setMenu(menu3);
    auto toolButton4 = new ToolButton(this);
    toolButton4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto toolButtonAction = new Action(IconType::CommentAdd, "评论", toolButton4);
    toolButtonAction->setCheckable(true);
    toolButtonAction->setChecked(true);
    toolButton4->setDefaultAction(toolButtonAction);
    auto *menu4 = new Menu(this);
    menu4->addAction(new QAction("样例1"));
    toolButton4->setMenu(menu4);
    auto toolBarAction = new Action(IconType::CommentAdd, "Action");
    toolBarAction->setDisabled(true);
    toolBarAction->setCheckable(true);
    toolBarAction->setChecked(true);
    toolBar->addCukeAction(toolBarAction);
    toolBar->addWidget(toolButton1);
    toolBar->addWidget(toolButton2);
    toolBar->addWidget(toolButton3);
    toolBar->addWidget(toolButton4);
    this->addToolBar(toolBar);

    auto center = new QWidget();
    setCentralWidget(center);

    auto layout = new QHBoxLayout(center);
    auto scrollArea = new ScrollArea(center);
    scrollArea->setWidgetResizable(true);
    layout->addWidget(scrollArea);

    auto scrollWidget = new QWidget(scrollArea);
    auto columnLayout = new QVBoxLayout(scrollWidget);
    columnLayout->setContentsMargins(0, 0, 0, 0);
    columnLayout->setSpacing(4);
    constexpr int controlHeight = 32;
    constexpr int borderRadius = 6;

    auto lineEdit = new LineEdit();
    lineEdit->setPlaceholderText("Enter text");
    lineEdit->setFixedSize(160, controlHeight);
    lineEdit->setBorderRadius(borderRadius);
    auto lineEditCard = new SettingsCard("LineEdit", lineEdit, scrollWidget);
    columnLayout->addWidget(lineEditCard);

    auto comboBox = new ComboBox();
    comboBox->addItems({"One", "Two", "Three"});
    comboBox->setFixedSize(120, controlHeight);
    comboBox->setBorderRadius(borderRadius);
    auto comboBoxCard = new SettingsCard("ComboBox", comboBox, scrollWidget);
    columnLayout->addWidget(comboBoxCard);

    auto slider = new Slider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(50);
    slider->setFixedSize(200, controlHeight);
    auto sliderCard = new SettingsCard("Slider", slider, scrollWidget);
    columnLayout->addWidget(sliderCard);

    auto toggleSwitch = new ToggleSwitch();
    toggleSwitch->setIsToggled(true);
    auto toggleSwitchCard = new SettingsCard("ToggleSwitch", toggleSwitch, scrollWidget);
    columnLayout->addWidget(toggleSwitchCard);
    columnLayout->addStretch();

    scrollArea->setWidget(scrollWidget);
}

MainWindow::~MainWindow() = default;

