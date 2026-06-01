#ifndef CUKECHECKBOX_H
#define CUKECHECKBOX_H
#include <QCheckBox>
#include <QColor>
#include <QVariantAnimation>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeCheckBoxPrivate;
class CUKE_EXPORT CukeCheckBox : public QCheckBox {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeCheckBox)
    CUKE_Q_PROPERTY_DECL(qreal, CheckProgress)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeCheckBox(const QString &text = QString(), QWidget *parent = nullptr);
    ~CukeCheckBox() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECHECKBOX_H
