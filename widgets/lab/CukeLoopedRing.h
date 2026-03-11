#ifndef CUKELOOPEDRING_H
#define CUKELOOPEDRING_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QPaintEvent>

#include "CukeProperty.h"
#include "CukeContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
CUKE_BEGIN_NAMESPACE(lab)
class CukeLoopedRingPrivate;
class CUKE_EXPORT CukeLoopedRing : public CukeContextMixin<QWidget> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeLoopedRing)
    CUKE_Q_PROPERTY_DECL(qreal, Angle)
public:
    explicit CukeLoopedRing(QWidget *parent = nullptr);
    ~CukeLoopedRing() override;

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

#endif // CUKELOOPEDRING_H
