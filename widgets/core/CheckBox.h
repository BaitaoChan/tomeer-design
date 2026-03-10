#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>
#include <QColor>
#include <QVariantAnimation>

#include "Property.h"
#include "ContextMixin.h"
CUKE_BEGIN_NAMESPACE(widget)
class CheckBoxPrivate;
class CUKE_EXPORT CheckBox : public ContextMixin<QCheckBox> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CheckBox)
    CUKE_Q_PROPERTY_DECL(qreal, CheckProgress)

public:
    explicit CheckBox(const QString &text = QString(), QWidget *parent = nullptr);
    ~CheckBox() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_END_NAMESPACE(widget)

#endif // CHECKBOX_H
