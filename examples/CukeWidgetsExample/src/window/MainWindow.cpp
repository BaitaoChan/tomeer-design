#include "MainWindow.h"

#include <QToolButton>
#include <QLayout>
#include <QMenuBar>
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
    setWindowTitle("CukeWidgetsExample");
    setWindowIcon(QIcon(":/images/Mortis.png"));
}

MainWindow::~MainWindow() = default;

