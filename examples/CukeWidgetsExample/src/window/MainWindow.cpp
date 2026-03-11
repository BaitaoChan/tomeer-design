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

    createMenuBar();
    createThemeButton();
    createToolBar();
    createStatusBar();
    createCentralWidget();
    createDockWidgets();
}

MainWindow::~MainWindow() = default;

void MainWindow::createThemeButton()
{
    auto *themeBtn = new QToolButton(this);
    themeBtn->setText("☀");
    themeBtn->setToolTip(tr("切换亮暗主题"));
    themeBtn->setAutoRaise(true);

    connect(themeBtn, &QToolButton::clicked, this, [this, themeBtn]() {
        if (pTheme->getThemeMode() == CukeThemeType::Light) {
            pTheme->setThemeMode(CukeThemeType::Dark);
            themeBtn->setText("🌙");
        } else {
            pTheme->setThemeMode(CukeThemeType::Light);
            themeBtn->setText("☀");
        }
    });

    auto *rightBox = new QWidget(this);
    auto *layout = new QHBoxLayout(rightBox);
    layout->setContentsMargins(0, 0, 6, 0);
    layout->setSpacing(0);
    layout->addWidget(themeBtn);

    menuBar->setCornerWidget(rightBox, Qt::TopRightCorner);
}

void MainWindow::createMenuBar() {
    menuBar = new CukeMenuBar(this);
    setMenuBar(menuBar);

    // File
    QMenu *fileMenu = menuBar->addMenu("&File");

    actionNew = new QAction("New", this);
    actionOpen = new QAction("Open", this);
    actionSave = new QAction("Save", this);
    actionExit = new QAction("Exit", this);

    fileMenu->addAction(actionNew);
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);
    fileMenu->addSeparator();
    fileMenu->addAction(actionExit);

    connect(actionExit, &QAction::triggered, this, &QWidget::close);

    // Edit
    QMenu *editMenu = menuBar->addMenu("&Edit");
    editMenu->addAction("Undo");
    editMenu->addAction("Redo");
    editMenu->addSeparator();
    editMenu->addAction("Copy");
    editMenu->addAction("Paste");

    // View
    QMenu *viewMenu = menuBar->addMenu("&View");

    // Help
    QMenu *helpMenu = menuBar->addMenu("&Help");
    helpMenu->addAction("About");
}

void MainWindow::createToolBar() {
    toolBar = new QToolBar("Main Toolbar", this);
    addToolBar(Qt::TopToolBarArea, toolBar);

    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    toolBar->addAction(actionSave);
}

void MainWindow::createStatusBar() {
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    statusBar->showMessage("Ready");
}

void MainWindow::createCentralWidget() {
    editor = new QTextEdit(this);
    editor->setPlaceholderText("Editor Area");

    setCentralWidget(editor);
}

void MainWindow::createDockWidgets() {
    // Left Navigation
    leftDock = new QDockWidget("Navigation", this);
    navigationTree = new QTreeWidget();

    navigationTree->setHeaderLabel("Project");

    auto root = new QTreeWidgetItem(navigationTree);
    root->setText(0, "CukeWidgets");

    auto item1 = new QTreeWidgetItem(root);
    item1->setText(0, "CukeMainWindow");

    auto item2 = new QTreeWidgetItem(root);
    item2->setText(0, "Widgets");

    navigationTree->expandAll();

    leftDock->setWidget(navigationTree);

    addDockWidget(Qt::LeftDockWidgetArea, leftDock);

    // Right Property Panel
    rightDock = new QDockWidget(tr("Properties"), this);

    propertyList = new QListWidget();

    propertyList->addItem("Width");
    propertyList->addItem("Height");
    propertyList->addItem("Color");
    propertyList->addItem("Font");

    rightDock->setWidget(propertyList);

    addDockWidget(Qt::RightDockWidgetArea, rightDock);
}
