#ifndef CUKEAPPBARBUTTON_H
#define CUKEAPPBARBUTTON_H
#include <QToolButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBarButtonPrivate;
class CukeAppBarButton : public QToolButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeAppBarButton)
    CUKE_Q_PROPERTY_DECL(bool, Hover)
    CUKE_Q_PROPERTY_DECL(bool, Pressed)
    CUKE_Q_PROPERTY_DECL(QColor, BgColor)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(bool, BgColorUsedFlag)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(CukeGeometryType::SideFlag, SideFlag)
public:
    explicit CukeAppBarButton(QWidget *parent = nullptr);
    ~CukeAppBarButton() override;

    void bgColorFrom(QColor color);
    void bgColorTo(QColor color);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEAPPBARBUTTON_H
