#ifndef CUKETOOLBUTTON_H
#define CUKETOOLBUTTON_H
#include <QToolButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolButtonPrivate;
class CUKE_EXPORT CukeToolButton : public QToolButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToolButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(qreal, RotateAngle)
    CUKE_Q_PROPERTY_DECL(CukeIconType::Icon, IconType)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(CukeGeometryType::SideFlag, SideFlag)
public:
    explicit CukeToolButton(QWidget *parent = nullptr);
    ~CukeToolButton() override;

    void setMenu(QMenu *menu);
    QMenu *menu() const;

protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTON_H
