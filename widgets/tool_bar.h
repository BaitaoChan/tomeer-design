#ifndef TOOL_BAR_H
#define TOOL_BAR_H
#include <QToolBar>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class Action;
class ToolBarPrivate;
class WIDGETS_EXPORT ToolBar : public QToolBar {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ToolBar)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    using QToolBar::addAction;

    explicit ToolBar(QWidget *parent = nullptr);
    ~ToolBar() override;

    Action *addAction(Action *action);

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // TOOL_BAR_H
