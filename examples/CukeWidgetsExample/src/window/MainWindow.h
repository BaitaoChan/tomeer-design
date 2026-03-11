#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CukeMenuBar.h"
#include "CukeWindow.h"

using namespace cuke::widget;

class QMenuBar;
class QToolBar;
class QStatusBar;

class QTextEdit;
class QDockWidget;
class QTreeWidget;
class QListWidget;

class QAction;

class MainWindow : public CukeWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void createThemeButton();
    void createMenuBar();
    void createToolBar();
    void createStatusBar();
    void createCentralWidget();
    void createDockWidgets();

private:
    CukeMenuBar *menuBar;
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
