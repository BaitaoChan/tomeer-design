#ifndef NAVIGATION_BAR_H
#define NAVIGATION_BAR_H
#include <QString>
#include <QWidget>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class NavigationBarPrivate;
class WIDGETS_EXPORT NavigationBar : public QWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(NavigationBar)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
    TOMEER_Q_PROPERTY_DECL(NavigationBarType::DisplayMode, DisplayMode)
public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar() override;

    bool addPageNode(QWidget *page, const QString &key, const QString &title, IconType::Icon icon = IconType::None, const QString &parentKey = {});
    bool addExpanderNode(const QString &key, const QString &title, IconType::Icon icon = IconType::None, const QString &parentKey = {});
    bool removeNode(const QString &key);

    bool setCurrentKey(const QString &key);
    QString currentKey() const;

    bool getIsCompacted() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // NAVIGATION_BAR_H
