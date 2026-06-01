#ifndef CUKELOOPEDRING_H
#define CUKELOOPEDRING_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QtMath>
#include <QPaintEvent>

#include "CukeObjectMap.h"
#include "CukeProperty.h"
#include "CukeType.h"

using namespace cuke::pub;

CUKE_NAMESPACE_BEGIN(lab)
class CukeLoopedRingPrivate;
class CUKE_EXPORT CukeLoopedRing : public QWidget {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeLoopedRing)
    CUKE_Q_PROPERTY_DECL(qreal, Angle)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
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
