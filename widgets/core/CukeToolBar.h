#ifndef CUKETOOLBAR_H
#define CUKETOOLBAR_H
#include <QToolBar>

#include "CukeHub.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CUKE_EXPORT CukeToolBar : public QToolBar, public CukeHub {
    Q_OBJECT
public:
    explicit CukeToolBar(QWidget *parent = nullptr);
    ~CukeToolBar() override;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBAR_H
