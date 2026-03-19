#ifndef CUKETOOLBUTTONPRIVATE_H
#define CUKETOOLBUTTONPRIVATE_H
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolButton;
class CukeToolButtonPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeToolButton)
public:
    explicit CukeToolButtonPrivate(CukeToolButton *parent = nullptr);
    ~CukeToolButtonPrivate() override;
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBUTTONPRIVATE_H
