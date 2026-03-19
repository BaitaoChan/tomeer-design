#ifndef CUKETOOLBUTTON_H
#define CUKETOOLBUTTON_H
#include <QToolButton>

#include "CukeContextMixin.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolButtonPrivate;
class CUKE_EXPORT CukeToolButton : public CukeContextMixin<QToolButton> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToolButton)
public:
    explicit CukeToolButton(QWidget *parent = nullptr);
    ~CukeToolButton() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTON_H
