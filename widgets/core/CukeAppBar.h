#ifndef CUKEAPPBAR_H
#define CUKEAPPBAR_H
#include <QWidget>

#include "CukeProperty.h"
#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeAppBarPrivate;
class CukeAppBar : public CukeContextMixin<QWidget> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeAppBar)
    CUKE_Q_PROPERTY_DECL(int, AppBarHeight)
public:
    explicit CukeAppBar(QWidget *parent = nullptr);
    ~CukeAppBar() override;

};

CUKE_NAMESPACE_END(widget)

#endif // CUKEAPPBAR_H
