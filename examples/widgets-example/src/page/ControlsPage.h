#ifndef CONTROLS_PAGE_H
#define CONTROLS_PAGE_H

#include "main.h"

class ControlsPage : public ScrollArea {
    Q_OBJECT
public:
    explicit ControlsPage(QWidget *parent = nullptr);
    ~ControlsPage() override;
};

#endif // CONTROLS_PAGE_H
