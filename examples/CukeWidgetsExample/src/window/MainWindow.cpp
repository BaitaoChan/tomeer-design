#include "MainWindow.h"

#include <QToolButton>
#include <QLayout>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>

#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>

#include <QMenu>
#include <QAction>

#include <QFile>

#include "CukeIcon.h"
#include "CukeAction.h"
#include "CukeMenu.h"
#include "CukeAppBar.h"
#include "CukeMenuBar.h"
#include "CukeToolBar.h"
#include "CukeToolButton.h"
#include "CukeComboBox.h"

MainWindow::MainWindow(QWidget *parent)
    : Window(parent) {
    // setWindowTitle("Widgets");
    setWindowIcon(QIcon(":/images/GreenSun.svg"));

    auto menuBar = new MenuBar(this);
    menuBar->addAction(new QAction("文件"));
    menuBar->addAction(new QAction("编辑"));
    menuBar->addAction(new QAction("视图"));
    menuBar->addAction(new QAction("项目"));
    menuBar->addAction(new QAction("生成"));
    menuBar->addAction(new QAction("调试"));
    menuBar->addAction(new QAction("拓展"));
    appBar()->addCustomWidget(menuBar, AppBarType::LeftArea);
    setDisplayMode(WindowType::MicaAlt);

    auto toolBar = new ToolBar(this);
    auto *toolButton1 = new ToolButton(this);
    toolButton1->setText("开始");
    auto *toolButton2 = new ToolButton(this);
    // toolButton2->setIcon(CUKE_ICON->getCukeIcon(IconType::CommentAdd, CUKE_THEME->getThemeColor(ThemeType::Text), 64));
    toolButton2->setIconType(IconType::BookCoins);
    auto *toolButton3 = new ToolButton(this);
    toolButton3->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton3->setText("统计");
    // toolButton3->setIcon(CUKE_ICON->getCukeIcon(IconType::Dismiss, CUKE_THEME->getThemeColor(ThemeType::Text), 64));
    toolButton3->setIconType(IconType::AppGeneric);
    auto menu3 = new Menu(this);
    menu3->addAction(new QAction("样例1"));
    menu3->addAction(new QAction("样例2"));
    menu3->addAction(new QAction("样例3"));

    auto sample4Action = new Action(IconType::CommentAdd, "样例4", menu3);
    sample4Action->setShortcut(QKeySequence("Ctrl+4"));
    sample4Action->setCheckable(true);
    sample4Action->setToolTip("这是样例4，用于测试 Action");
    sample4Action->setStatusTip("触发样例4 Action");
    menu3->addAction(sample4Action);

    auto subMenu = new Menu("更多", menu3);
    subMenu->setIconType(IconType::Desktop);
    subMenu->addAction(new Action("子项1", subMenu));
    subMenu->addAction(new Action(IconType::BookCoins, "子项2", subMenu));
    auto *subAction = menu3->addCukeMenu(subMenu);
    subAction->setShortcut(QKeySequence("Ctrl+M"));

    toolButton3->setMenu(menu3);
    auto *toolButton4 = new ToolButton(this);
    toolButton4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton4->setText("评论");
    toolButton4->setIconType(IconType::CommentAdd);
    auto *menu4 = new Menu(this);
    menu4->addAction(new QAction("样例1"));
    toolButton4->setMenu(menu4);
    toolBar->addWidget(toolButton1);
    toolBar->addWidget(toolButton2);
    toolBar->addWidget(toolButton3);
    toolBar->addWidget(toolButton4);
    this->addToolBar(toolBar);

    auto center = new QWidget();
    setCentralWidget(center);

    auto *layout = new QHBoxLayout(center);
    auto combo = new ComboBox(this);
    combo->setFixedSize(60, 30);
    combo->addItems({"一号", "二号", "三号"});
    layout->addWidget(combo);
}

MainWindow::~MainWindow() = default;

