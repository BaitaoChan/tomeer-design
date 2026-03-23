#include "CukePainter.h"

CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_SINGLETON_IMPL(CukePainter)
CukePainter::CukePainter(QObject *parent)
    : QObject(parent) {
}

CukePainter::~CukePainter() = default;

void CukePainter::drawRoundedRect(const QRect &rect, QPainter *painter, qreal xRadius, qreal yRadius, CukeGeometryType::SideFlag flag) {
    if (!painter || rect.isEmpty())
        return;

    QPainterPath path;
    path.moveTo(QRectF(rect).left() + (flag & CukeGeometryType::TopLeft ? xRadius : 0), QRectF(rect).top());
    path.lineTo(QRectF(rect).right() - (flag & CukeGeometryType::TopRight ? xRadius : 0), QRectF(rect).top());
    if (flag & CukeGeometryType::TopRight) {
        path.arcTo(QRectF(QRectF(rect).right() - 2 * xRadius, QRectF(rect).top(), 2 * xRadius, 2 * yRadius), 90, -90);
    } else {
        path.lineTo(QRectF(rect).right(), QRectF(rect).top());
    }

    path.lineTo(QRectF(rect).right(), QRectF(rect).bottom() - (flag & CukeGeometryType::BottomRight ? yRadius : 0));
    if (flag & CukeGeometryType::BottomRight) {
        path.arcTo(QRectF(QRectF(rect).right() - 2 * xRadius, QRectF(rect).bottom() - 2 * yRadius, 2 * xRadius,
                          2 * yRadius), 0, -90);
    } else {
        path.lineTo(QRectF(rect).right(), QRectF(rect).bottom());
    }

    path.lineTo(QRectF(rect).left() + (flag & CukeGeometryType::BottomLeft ? xRadius : 0), QRectF(rect).bottom());
    if (flag & CukeGeometryType::BottomLeft) {
        path.arcTo(QRectF(QRectF(rect).left(), QRectF(rect).bottom() - 2 * yRadius, 2 * xRadius, 2 * yRadius), 270,
                   -90);
    } else {
        path.lineTo(QRectF(rect).left(), QRectF(rect).bottom());
    }

    path.lineTo(QRectF(rect).left(), QRectF(rect).top() + (flag & CukeGeometryType::TopLeft ? yRadius : 0));
    if (flag & CukeGeometryType::TopLeft) {
        path.arcTo(QRectF(QRectF(rect).left(), QRectF(rect).top(), 2 * xRadius, 2 * yRadius), 180, -90);
    } else {
        path.lineTo(QRectF(rect).left(), QRectF(rect).top());
    }

    path.closeSubpath();
    painter->drawPath(path);
}

CUKE_NAMESPACE_END(pub)