#ifndef CUKELABEL_H
#define CUKELABEL_H
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPainter>

#include "CukeContextMixin.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeLabelPrivate;
class CUKE_EXPORT CukeLabel : public CukeContextMixin<QLabel> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeLabel)
    CUKE_Q_PROPERTY_DECL(QColor, TextColor)
public:
    explicit CukeLabel(QWidget *parent = nullptr);
    explicit CukeLabel(const QString &text, QWidget *parent = nullptr);
    explicit CukeLabel(const QString &text, const QColor &color, QWidget *parent = nullptr);
    ~CukeLabel() override;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKELABEL_H
