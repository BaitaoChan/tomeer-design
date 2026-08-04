#ifndef CUKEPUSHBUTTON_H
#define CUKEPUSHBUTTON_H
#include <QAbstractButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class PushButtonPrivate;
class CUKE_EXPORT PushButton : public QAbstractButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(PushButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(IconType::Icon, CukeIcon)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    explicit PushButton(QWidget *parent = nullptr);
    explicit PushButton(const QString &text, QWidget *parent = nullptr);
    explicit PushButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    explicit PushButton(const IconType::Icon &icon, const QString &text, QWidget *parent = nullptr);
    ~PushButton() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEPUSHBUTTON_H