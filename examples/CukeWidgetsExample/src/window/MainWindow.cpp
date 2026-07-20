#include "MainWindow.h"

#include <QLayout>
#include <QGridLayout>
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
#include "CukeLabel.h"
#include "CukeLineEdit.h"
#include "CukeComboBox.h"
#include "CukePushButton.h"
#include "CukeSlider.h"
#include "CukeToggleButton.h"
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
    setDisplayMode(WindowType::MicaAlt);

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
    auto gridLayout = new QGridLayout(scrollWidget);
    gridLayout->setColumnStretch(0, 1);
    gridLayout->setColumnStretch(1, 1);
    constexpr int controlHeight = 32;
    constexpr int borderRadius = 6;

    auto lineEditLabel = new Label("LineEdit", scrollWidget);
    auto lineEdit = new LineEdit(scrollWidget);
    lineEdit->setPlaceholderText("Enter text");
    lineEdit->setFixedSize(160, controlHeight);
    lineEdit->setBorderRadius(borderRadius);
    gridLayout->addWidget(lineEditLabel, 0, 0);
    gridLayout->addWidget(lineEdit, 0, 1);

    auto comboBoxLabel = new Label("ComboBox", scrollWidget);
    auto comboBox = new ComboBox(scrollWidget);
    comboBox->addItems({"One", "Two", "Three"});
    comboBox->setFixedSize(120, controlHeight);
    comboBox->setBorderRadius(borderRadius);
    gridLayout->addWidget(comboBoxLabel, 1, 0);
    gridLayout->addWidget(comboBox, 1, 1);

    auto pushButtonLabel = new Label("PushButton", scrollWidget);
    auto pushButton = new PushButton("Button", scrollWidget);
    pushButton->setFixedSize(100, controlHeight);
    pushButton->setBorderRadius(borderRadius);
    gridLayout->addWidget(pushButtonLabel, 2, 0);
    gridLayout->addWidget(pushButton, 2, 1);

    auto sliderLabel = new Label("Slider", scrollWidget);
    auto slider = new Slider(Qt::Horizontal, scrollWidget);
    slider->setRange(0, 100);
    slider->setValue(50);
    slider->setFixedSize(200, controlHeight);
    gridLayout->addWidget(sliderLabel, 3, 0);
    gridLayout->addWidget(slider, 3, 1);

    auto toggleButtonLabel = new Label("ToggleButton", scrollWidget);
    auto toggleButton = new ToggleButton("Toggle", scrollWidget);
    toggleButton->setIsToggled(true);
    toggleButton->setFixedSize(100, controlHeight);
    toggleButton->setBorderRadius(borderRadius);
    gridLayout->addWidget(toggleButtonLabel, 4, 0);
    gridLayout->addWidget(toggleButton, 4, 1);

    auto toggleSwitchLabel = new Label("ToggleSwitch", scrollWidget);
    auto toggleSwitch = new ToggleSwitch(scrollWidget);
    toggleSwitch->setIsToggled(true);
    gridLayout->addWidget(toggleSwitchLabel, 5, 0);
    gridLayout->addWidget(toggleSwitch, 5, 1);

    for (int row = 0; row < gridLayout->rowCount(); ++row) {
        gridLayout->setRowMinimumHeight(row, 40);
        gridLayout->itemAtPosition(row, 0)->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        gridLayout->itemAtPosition(row, 1)->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
    gridLayout->setRowStretch(gridLayout->rowCount(), 1);
    scrollArea->setWidget(scrollWidget);
}

MainWindow::~MainWindow() = default;

