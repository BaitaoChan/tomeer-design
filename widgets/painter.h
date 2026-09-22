#ifndef PAINTER_H
#define PAINTER_H
#include <QPainter>
#include <QPainterPath>

#include "property.h"
#include "type.h"

#define TOMEER_PAINTER Painter::instance()

TOMEER_NAMESPACE_BEGIN()
class WIDGETS_EXPORT Painter : public QObject {
    Q_OBJECT
    TOMEER_Q_SINGLETON_DECL(Painter)
private:
    explicit Painter(QObject *parent = nullptr);
    ~Painter() override;
public:
    inline void drawRoundedRect(const QRect &rect, QPainter *painter, qreal xRadius, qreal yRadius, GeometryType::SideFlag flag = GeometryType::All);

    inline void drawIcon(const QPointF &center, QPainter *painter, const QIcon &icon, const QSize &size = QSize(24, 24));


};
TOMEER_NAMESPACE_END

#endif // PAINTER_H
