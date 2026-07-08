#ifndef CUKECHECKBOX_H
#define CUKECHECKBOX_H
#include <QCheckBox>
#include <QColor>
#include <QVariantAnimation>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CheckBoxPrivate;
class CUKE_EXPORT CheckBox : public QCheckBox {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CheckBox)
    CUKE_Q_PROPERTY_DECL(qreal, CheckProgress)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit CheckBox(const QString &text = QString(), QWidget *parent = nullptr);
    ~CheckBox() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECHECKBOX_H
