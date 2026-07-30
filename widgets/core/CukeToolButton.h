#ifndef CUKETOOLBUTTON_H
#define CUKETOOLBUTTON_H
#include <QToolButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToolButtonPrivate;
class CUKE_EXPORT ToolButton : public QToolButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToolButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(qreal, RotateAngle)
    CUKE_Q_PROPERTY_DECL(IconType::Icon, CukeIcon)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    explicit ToolButton(QWidget *parent = nullptr);
    ~ToolButton() override;

    void setMenu(QMenu *menu);
    QMenu *menu() const;

protected:
    bool event(QEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTON_H