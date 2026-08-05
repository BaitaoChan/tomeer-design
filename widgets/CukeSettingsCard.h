#ifndef CUKESETTINGSCARD_H
#define CUKESETTINGSCARD_H
#include <QWidget>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class CUKE_EXPORT SettingsCard : public QWidget {
    Q_OBJECT
    CUKE_Q_PROPERTY_DECL(QString, Header)
    CUKE_Q_PROPERTY_DECL(QWidget *, Content)
public:
    explicit SettingsCard(QWidget *parent = nullptr);
    explicit SettingsCard(const QString &header, QWidget *content = nullptr, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END

#endif // CUKESETTINGSCARD_H