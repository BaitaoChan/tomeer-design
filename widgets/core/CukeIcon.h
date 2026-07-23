#ifndef CUKEICON_H
#define CUKEICON_H
#include <QIcon>

#include "CukeProperty.h"
#include "CukeType.h"

#define CUKE_ICON Icon::instance()

CUKE_NAMESPACE_BEGIN(pub)
    class CUKE_EXPORT Icon : public QObject {
    Q_OBJECT
    CUKE_Q_SINGLETON_DECL(Icon)
private:
    explicit Icon(QObject *parent = nullptr);
    ~Icon() override;
public:
    QIcon getCukeIcon(IconType::Icon glyph);
    QIcon getCukeIcon(IconType::Icon glyph, QColor color);
    QIcon getCukeIcon(IconType::Icon glyph, QColor color, int pixelSize);
};

CUKE_NAMESPACE_END(pub)

#endif // CUKEICON_H