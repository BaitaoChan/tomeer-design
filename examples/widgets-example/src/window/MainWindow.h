#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "menu_bar.h"
#include "window.h"

using namespace tomeer;

class MainWindow : public Window {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif // MAIN_WINDOW_H