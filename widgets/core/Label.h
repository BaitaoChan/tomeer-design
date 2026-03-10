#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPainter>

#include "ContextMixin.h"
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class LabelPrivate;
class CUKE_EXPORT Label : public ContextMixin<QLabel> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Label)
    CUKE_Q_PROPERTY_DECL(QColor, TextColor)
public:
    explicit Label(QWidget *parent = nullptr);
    explicit Label(const QString &text, QWidget *parent = nullptr);
    explicit Label(const QString &text, const QColor &color, QWidget *parent = nullptr);
    ~Label() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_END_NAMESPACE(widget)

#endif // LABEL_H
