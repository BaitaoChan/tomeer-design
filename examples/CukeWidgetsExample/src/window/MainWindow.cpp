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
#include "CukeAppBar.h"
#include "CukeMenuBar.h"
#include "CukeToolBar.h"
#include "CukeToolButton.h"

MainWindow::MainWindow(QWidget *parent)
    : CukeWindow(parent) {
    // setWindowTitle("CukeWidgets");
    setWindowIcon(QIcon(":/images/GreenSun.svg"));

    auto menuBar = new CukeMenuBar(this);
    menuBar->addAction(new QAction("文件"));
    menuBar->addAction(new QAction("编辑"));
    menuBar->addAction(new QAction("视图"));
    menuBar->addAction(new QAction("项目"));
    menuBar->addAction(new QAction("生成"));
    menuBar->addAction(new QAction("调试"));
    menuBar->addAction(new QAction("拓展"));
    appBar()->addCustomWidget(menuBar, CukeAppBarType::LeftArea);

    auto toolBar = new CukeToolBar(this);
    auto *toolButton1 = new CukeToolButton(this);
    toolButton1->setText("开始");
    auto *toolButton2 = new CukeToolButton(this);
    toolButton2->setIcon(cIcon->getCukeIcon(CukeIconType::CommentAdd, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text), 64));
    // toolButton2->setIconType(CukeIconType::BookCoins);
    // auto *toolButton3 = new CukeToolButton(this);
    // toolButton3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // toolButton3->setText("结束");
    // toolButton3->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text), 64));
    // toolButton3->setIconType(CukeIconType::Battery2);
    auto *toolButton4 = new CukeToolButton(this);
    toolButton4->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton4->setText("评论");
    toolButton4->setIcon(cIcon->getCukeIcon(CukeIconType::Dismiss, cTheme->getThemeColor(getThemeMode(), CukeThemeType::Text), 64));
    toolButton4->setIconType(CukeIconType::CommentAdd);
    toolBar->addWidget(toolButton1);
    toolBar->addWidget(toolButton2);
    // toolBar->addWidget(toolButton3);
    toolBar->addWidget(toolButton4);
    this->addToolBar(toolBar);
}

MainWindow::~MainWindow() = default;

