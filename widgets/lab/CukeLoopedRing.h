#ifndef CUKELOOPEDRING_H
#define CUKELOOPEDRING_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QPaintEvent>

#include "CukeScope.h"
#include "CukeProperty.h"

using namespace cuke::pub;

CUKE_NAMESPACE_BEGIN(lab)
class CukeLoopedRingPrivate;
class CUKE_EXPORT CukeLoopedRing : public QWidget, public CukeScope {
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
CUKE_NAMESPACE_END(lab)

#endif // CUKELOOPEDRING_H
