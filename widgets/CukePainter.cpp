#include "CukePainter.h"
#include "CukeIcon.h"

CUKE_NAMESPACE_BEGIN()
CUKE_Q_SINGLETON_IMPL(Painter)
Painter::Painter(QObject *parent)
    : QObject(parent) {
}

Painter::~Painter() = default;

void Painter::drawRoundedRect(const QRect &rect, QPainter *painter, qreal xRadius, qreal yRadius, GeometryType::SideFlag flag) {
    if (!painter || rect.isEmpty())
        return;

    QPainterPath path;
    path.moveTo(QRectF(rect).left() + (flag & GeometryType::TopLeft ? xRadius : 0), QRectF(rect).top());
    path.lineTo(QRectF(rect).right() - (flag & GeometryType::TopRight ? xRadius : 0), QRectF(rect).top());
    if (flag & GeometryType::TopRight) {
        path.arcTo(QRectF(QRectF(rect).right() - 2 * xRadius, QRectF(rect).top(), 2 * xRadius, 2 * yRadius), 90, -90);
    } else {
        path.lineTo(QRectF(rect).right(), QRectF(rect).top());
    }

    path.lineTo(QRectF(rect).right(), QRectF(rect).bottom() - (flag & GeometryType::BottomRight ? yRadius : 0));
    if (flag & GeometryType::BottomRight) {
        path.arcTo(QRectF(QRectF(rect).right() - 2 * xRadius, QRectF(rect).bottom() - 2 * yRadius, 2 * xRadius,
                          2 * yRadius), 0, -90);
    } else {
        path.lineTo(QRectF(rect).right(), QRectF(rect).bottom());
    }

    path.lineTo(QRectF(rect).left() + (flag & GeometryType::BottomLeft ? xRadius : 0), QRectF(rect).bottom());
    if (flag & GeometryType::BottomLeft) {
        path.arcTo(QRectF(QRectF(rect).left(), QRectF(rect).bottom() - 2 * yRadius, 2 * xRadius, 2 * yRadius), 270,
                   -90);
    } else {
        path.lineTo(QRectF(rect).left(), QRectF(rect).bottom());
    }

    path.lineTo(QRectF(rect).left(), QRectF(rect).top() + (flag & GeometryType::TopLeft ? yRadius : 0));
    if (flag & GeometryType::TopLeft) {
        path.arcTo(QRectF(QRectF(rect).left(), QRectF(rect).top(), 2 * xRadius, 2 * yRadius), 180, -90);
    } else {
        path.lineTo(QRectF(rect).left(), QRectF(rect).top());
    }

    path.closeSubpath();
    painter->drawPath(path);
}

void Painter::drawIcon(const QPointF &center, QPainter *painter, const QIcon &icon, const QSize &size) {
    if (!painter || icon.isNull())
        return;

    painter->drawPixmap(QRect(QPointF(center.x() - size.width() / 2.0,
                                      center.y() - size.height() / 2.0).toPoint(), size),
                        icon.pixmap(size));
}

CUKE_NAMESPACE_END