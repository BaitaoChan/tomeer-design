#ifndef CUKEMENU_H
#define CUKEMENU_H
#include <QMenu>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenuPrivate;
class CUKE_EXPORT CukeMenu : public QMenu {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeMenu)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeMenu(QWidget* parent = nullptr);
    explicit CukeMenu(const QString &title, QWidget *parent = nullptr);
    ~CukeMenu() override;

protected:
    void showEvent(QShowEvent *event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};

CUKE_NAMESPACE_END(pub)

#endif // CUKEMENU_H
