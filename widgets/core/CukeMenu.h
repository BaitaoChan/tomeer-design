#ifndef CUKEMENU_H
#define CUKEMENU_H
#include <QMenu>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class Action;
class MenuPrivate;
class CUKE_EXPORT Menu : public QMenu {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Menu)
    CUKE_Q_PROPERTY_DECL(IconType::Icon, CukeIcon)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit Menu(QWidget* parent = nullptr);
    explicit Menu(const QString &title, QWidget *parent = nullptr);
    ~Menu() override;

    Action *addCukeMenu(Menu *menu);

protected:
    void showEvent(QShowEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};

CUKE_NAMESPACE_END(pub)

#endif // CUKEMENU_H