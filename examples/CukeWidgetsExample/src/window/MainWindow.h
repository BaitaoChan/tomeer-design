#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CukeMenuBar.h"
#include "CukeWindow.h"

using namespace cuke;

class MainWindow : public Window {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif // MAINWINDOW_H
