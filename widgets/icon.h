#ifndef ICON_H
#define ICON_H
#include <QIcon>

#include "property.h"
#include "type.h"

#define TOMEER_ICON Icon::instance()

TOMEER_NAMESPACE_BEGIN()
    class WIDGETS_EXPORT Icon : public QObject {
    Q_OBJECT
    TOMEER_Q_SINGLETON_DECL(Icon)
private:
    explicit Icon(QObject *parent = nullptr);
    ~Icon() override;
public:
    QIcon getIcon(IconType::Icon glyph);
    QIcon getIcon(IconType::Icon glyph, QColor color);
    QIcon getIcon(IconType::Icon glyph, QColor color, int pixelSize);
};

TOMEER_NAMESPACE_END

#endif // ICON_H
