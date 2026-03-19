#ifndef CUKEICON_H
#define CUKEICON_H
#include <QIcon>

#include "CukeProperty.h"
#include "CukeType.h"

#define cIcon CukeIcon::instance()

CUKE_NAMESPACE_BEGIN(pub)
    class CUKE_EXPORT CukeIcon : public QObject {
    Q_OBJECT
    CUKE_Q_SINGLETON_DECL(CukeIcon)
private:
    explicit CukeIcon(QObject *parent = nullptr);
    ~CukeIcon() override;
public:
    QIcon getCukeIcon(CukeIconType::Glyph glyph);
    QIcon getCukeIcon(CukeIconType::Glyph glyph, QColor color);
    QIcon getCukeIcon(CukeIconType::Glyph glyph, QColor color, int pixelSize);
};

CUKE_NAMESPACE_END(pub)

#endif // CUKEICON_H
