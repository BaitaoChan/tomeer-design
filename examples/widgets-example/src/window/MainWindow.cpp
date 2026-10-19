#include "MainWindow.h"

#include <QAction>
#include <QActionGroup>
#include <QWidget>

#include "action.h"
#include "app_bar.h"
#include "icon.h"
#include "menu.h"
#include "menu_bar.h"
#include "navigation_bar.h"
#include "tool_bar.h"
#include "tool_button.h"

#include "ControlsPage.h"

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
    setDisplayMode(WindowType::Acrylic);

    auto toolBar = new ToolBar(this);
    auto toolButton1 = new ToolButton(this);
    toolButton1->setText("开始");
    auto toolButton2 = new ToolButton(this);
    // toolButton2->setIcon(TOMEER_ICON->getIcon(IconType::CommentAdd, TOMEER_THEME->getThemeColor(ThemeType::Text), 64));
    toolButton2->setIcon(IconType::BookCoins);
    auto toolButton3 = new ToolButton(this);
    toolButton3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton3->setText("统计");
    // toolButton3->setIcon(TOMEER_ICON->getIcon(IconType::Dismiss, TOMEER_THEME->getThemeColor(ThemeType::Text), 64));
    toolButton3->setIcon(IconType::AppGeneric);
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
    subMenu->setIcon(IconType::Desktop);
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
    auto subAction = menu3->addMenu(subMenu);
    subAction->setShortcut(QKeySequence("Ctrl+M"));

    toolButton3->setMenu(menu3);
    auto toolButton4 = new ToolButton(this);
    toolButton4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto toolButtonAction = new Action(IconType::CommentAdd, "评论", toolButton4);
    toolButtonAction->setCheckable(true);
    toolButtonAction->setChecked(true);
    toolButton4->setDefaultAction(toolButtonAction);
    auto menu4 = new Menu(this);
    menu4->addAction(new QAction("样例1"));
    toolButton4->setMenu(menu4);
    auto toolBarAction = new Action(IconType::CommentAdd, "Action");
    toolBarAction->setDisabled(true);
    toolBarAction->setCheckable(true);
    toolBarAction->setChecked(true);
    toolBar->addAction(toolBarAction);
    toolBar->addWidget(toolButton1);
    toolBar->addWidget(toolButton2);
    toolBar->addWidget(toolButton3);
    toolBar->addWidget(toolButton4);
    this->addToolBar(toolBar);

    auto navigationBar = new NavigationBar(this);
    setCentralWidget(navigationBar);

    navigationBar->addExpanderNode("controls", "控件示例", IconType::Apps);
    navigationBar->addPageNode(new ControlsPage(navigationBar), "allControls", "全部控件", IconType::ControlButton, "controls");

    navigationBar->addExpanderNode("documents", "文档", IconType::Document);
    navigationBar->addPageNode(new QWidget(navigationBar), "recentDocuments", "最近使用", IconType::DocumentText, "documents");
    navigationBar->addPageNode(new QWidget(navigationBar), "favoriteDocuments", "收藏", IconType::Bookmark, "documents");

    navigationBar->addExpanderNode("workspace", "工作区", IconType::Folder);
    navigationBar->addPageNode(new QWidget(navigationBar), "projects", "项目", IconType::AppFolder, "workspace");
    navigationBar->addPageNode(new QWidget(navigationBar), "resources", "资源", IconType::Database, "workspace");

    navigationBar->addExpanderNode("system", "系统", IconType::Desktop);
    navigationBar->addPageNode(new QWidget(navigationBar), "settings", "设置", IconType::Settings, "system");
    navigationBar->addPageNode(new QWidget(navigationBar), "about", "关于", IconType::Info, "system");

    navigationBar->setCurrentKey("allControls");

    navigationBar->setDisplayMode(NavigationBarType::Auto);
}

MainWindow::~MainWindow() = default;
