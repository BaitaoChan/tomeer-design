#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CukeMenuBar.h"
#include "CukeWindow.h"

using namespace cuke::pub;

class MainWindow : public CukeWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif
