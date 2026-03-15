#ifndef CUKETOOLBAR_H
#define CUKETOOLBAR_H
#include <QToolBar>

#include "CukeContextMixin.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeToolBar : public CukeContextMixin<QToolBar> {
    Q_OBJECT
public:
    explicit CukeToolBar(QWidget *parent = nullptr);
    ~CukeToolBar() override;
};
CUKE_NAMESPACE_END(widget)

#endif //CUKETOOLBAR_H
