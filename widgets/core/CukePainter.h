#ifndef CUKEPAINTER_H
#define CUKEPAINTER_H
#include <QPainter>
#include <QPainterPath>

#include "CukeProperty.h"
#include "CukeType.h"

#define CUKE_PAINTER CukePainter::instance()

CUKE_NAMESPACE_BEGIN(pub)
class CUKE_EXPORT CukePainter : public QObject {
    Q_OBJECT
    CUKE_Q_SINGLETON_DECL(CukePainter)
private:
    explicit CukePainter(QObject *parent = nullptr);
    ~CukePainter() override;
public:
    inline void drawRoundedRect(const QRect &rect, QPainter *painter, qreal xRadius, qreal yRadius, CukeGeometryType::SideFlag flag = CukeGeometryType::All);

    inline void drawIcon(const QPointF &center, QPainter *painter, const QIcon &icon, const QSize &size = QSize(24, 24));


};
CUKE_NAMESPACE_END(pub)

#endif // CUKEPAINTER_H
