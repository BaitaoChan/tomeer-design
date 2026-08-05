#ifndef CUKETOGGLEBUTTON_H
#define CUKETOGGLEBUTTON_H
#include <QAbstractButton>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class ToggleButtonPrivate;
class CUKE_EXPORT ToggleButton : public QAbstractButton {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToggleButton)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(IconType::Icon, CukeIcon)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    CUKE_Q_PROPERTY_DECL(GeometryType::SideFlag, SideFlag)
public:
    explicit ToggleButton(QWidget *parent = nullptr);
    explicit ToggleButton(const QString &text, QWidget *parent = nullptr);
    explicit ToggleButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);
    explicit ToggleButton(const IconType::Icon &icon, const QString &text, QWidget *parent = nullptr);
    ~ToggleButton() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END

#endif // CUKETOGGLEBUTTON_H