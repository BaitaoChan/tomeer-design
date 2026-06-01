#include "MainWindow.h"

#include <QToolButton>
#include <QLayout>
#include "CukeMenuBar.h"
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>

#include <QDockWidget>
#include <QTreeWidget>
#include <QListWidget>

#include <QMenu>
#include <QAction>

#include <QFile>

#include "CukeAppBar.h"

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
}

MainWindow::~MainWindow() = default;

