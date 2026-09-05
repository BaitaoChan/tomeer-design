#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "main.h"

class MainWindow : public Window {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif // MAIN_WINDOW_H