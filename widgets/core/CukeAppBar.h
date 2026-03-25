#ifndef CUKEAPPBAR_H
#define CUKEAPPBAR_H
#include <QWidget>

#include "CukeHub.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBarPrivate;
class CukeAppBar : public QWidget, public CukeHub {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeAppBar)
    CUKE_Q_PROPERTY_DECL(int, AppBarHeight)
public:
    explicit CukeAppBar(QWidget *parent = nullptr);
    ~CukeAppBar() override;

protected:
    void onThemeChanged(CukeThemeType::ThemeMode mode) override;

};

CUKE_NAMESPACE_END(pub)

#endif // CUKEAPPBAR_H
