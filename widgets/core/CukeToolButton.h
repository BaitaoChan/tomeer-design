#ifndef CUKETOOLBUTTON_H
#define CUKETOOLBUTTON_H
#include <QToolButton>

#include "CukeScope.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeToolButtonPrivate;
class CUKE_EXPORT CukeToolButton : public QToolButton, public CukeScope {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeToolButton)
    CUKE_Q_PROPERTY_DECL(bool, Hover)
    CUKE_Q_PROPERTY_DECL(bool, Pressed)
    CUKE_Q_PROPERTY_DECL(QColor, BgColor)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(bool, BgColorUsedFlag)
    CUKE_Q_PROPERTY_DECL(CukeGeometryType::SideFlag, SideFlag)
public:
    explicit CukeToolButton(QWidget *parent = nullptr);
    ~CukeToolButton() override;

    void bgColorFrom(QColor color);
    void bgColorTo(QColor color);

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLBUTTON_H
