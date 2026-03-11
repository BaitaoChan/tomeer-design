#ifndef CUKECHECKBOX_H
#define CUKECHECKBOX_H
#include <QCheckBox>
#include <QColor>
#include <QVariantAnimation>

#include "CukeProperty.h"
#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class CukeCheckBoxPrivate;
class CUKE_EXPORT CukeCheckBox : public CukeContextMixin<QCheckBox> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeCheckBox)
    CUKE_Q_PROPERTY_DECL(qreal, CheckProgress)

public:
    explicit CukeCheckBox(const QString &text = QString(), QWidget *parent = nullptr);
    ~CukeCheckBox() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_END_NAMESPACE(widget)

#endif // CUKECHECKBOX_H
