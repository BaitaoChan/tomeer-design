#ifndef CUKETOOLBAR_H
#define CUKETOOLBAR_H
#include <QToolBar>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolBarPrivate;
class CUKE_EXPORT CukeToolBar : public QToolBar {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToolBar)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeToolBar(QWidget *parent = nullptr);
    ~CukeToolBar() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBAR_H
