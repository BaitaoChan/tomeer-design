#ifndef SETTINGS_CARD_H
#define SETTINGS_CARD_H
#include <QWidget>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class WIDGETS_EXPORT SettingsCard : public QWidget {
    Q_OBJECT
    TOMEER_Q_PROPERTY_DECL(QString, Header)
    TOMEER_Q_PROPERTY_DECL(QWidget *, Content)
public:
    explicit SettingsCard(QWidget *parent = nullptr);
    explicit SettingsCard(const QString &header, QWidget *content = nullptr, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};
TOMEER_NAMESPACE_END

#endif // SETTINGS_CARD_H