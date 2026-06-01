#ifndef CUKETOOLBARPRIVATE_H
#define CUKETOOLBARPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolBar;
class CukeToolBarPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeToolBar)
public:
    explicit CukeToolBarPrivate(CukeToolBar *q);
    ~CukeToolBarPrivate() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBARPRIVATE_H
