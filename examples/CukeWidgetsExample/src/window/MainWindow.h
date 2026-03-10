#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MenuBar.h"
#include "Window.h"

using namespace cuke;

class QMenuBar;
class QToolBar;
class QStatusBar;

class QTextEdit;
class QDockWidget;
class QTreeWidget;
class QListWidget;

class QAction;

class MainWindow : public widget::Window {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    void createCentralWidget();
    void createDockWidgets();

private:
    widget::MenuBar *menuBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QTextEdit *editor;
    QDockWidget *leftDock;
    QDockWidget *rightDock;
    QTreeWidget *navigationTree;
    QListWidget *propertyList;
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
};

#endif
