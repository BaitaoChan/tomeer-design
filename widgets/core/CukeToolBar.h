#ifndef CUKETOOLBAR_H
#define CUKETOOLBAR_H
#include <QToolBar>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToolBarPrivate;
class CUKE_EXPORT ToolBar : public QToolBar {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToolBar)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif //CUKETOOLBAR_H
