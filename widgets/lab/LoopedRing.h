#ifndef LOOPEDRING_H
#define LOOPEDRING_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QPaintEvent>

#include "Property.h"
#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
CUKE_BEGIN_NAMESPACE(lab)
class LoopedRingPrivate;
class CUKE_EXPORT LoopedRing : public ContextMixin<QWidget> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(LoopedRing)
    CUKE_Q_PROPERTY_DECL(qreal, Angle)
public:
    explicit LoopedRing(QWidget *parent = nullptr);
    ~LoopedRing() override;

    void setText(const QString &text);

public slots:
    void start() const;
    void stop() const;
    void exec() const;

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_END_NAMESPACE(lab)
CUKE_END_NAMESPACE(widget)

#endif // LOOPEDRING_H
