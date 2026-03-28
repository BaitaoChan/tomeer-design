#ifndef CUKECHECKBOX_H
#define CUKECHECKBOX_H
#include <QCheckBox>
#include <QColor>
#include <QVariantAnimation>

#include "CukeScope.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeCheckBoxPrivate;
class CUKE_EXPORT CukeCheckBox : public QCheckBox, public CukeScope {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeCheckBox)
    CUKE_Q_PROPERTY_DECL(qreal, CheckProgress)

public:
    explicit CukeCheckBox(const QString &text = QString(), QWidget *parent = nullptr);
    ~CukeCheckBox() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECHECKBOX_H
