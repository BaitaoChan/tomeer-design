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

MainWindow::MainWindow(QWidget *parent)
    : CukeWindow(parent) {
    // setWindowTitle("CukeWidgets");
    setWindowIcon(QIcon(":/images/Mortis.png"));

    auto menuBar = new CukeMenuBar(this);
    menuBar->addAction(new QAction("Open"));
    menuBar->addAction(new QAction("Close"));
    setMenuBar(menuBar);
}

MainWindow::~MainWindow() = default;

