#include <QPainter>
#include "CukeIcon.h"
CUKE_NAMESPACE_BEGIN(pub)
CUKE_Q_SINGLETON_IMPL(Icon)
Icon::Icon(QObject *parent)
    : QObject(parent) {
}

Icon::~Icon() = default;

QIcon Icon::getCukeIcon(IconType::Icon glyph) {
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform);

    QFont font("cuke");
    font.setPixelSize(32);
    painter.setFont(font);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(QChar(glyph)));

    return QIcon(pixmap);
}

QIcon Icon::getCukeIcon(IconType::Icon glyph, QColor color) {
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform);

    QFont font("cuke");
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(color);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(QChar(glyph)));

    return QIcon(pixmap);
}

QIcon Icon::getCukeIcon(IconType::Icon glyph, QColor color, int pixelSize) {
    QPixmap pixmap(pixelSize, pixelSize);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform);

    QFont font("cuke");
    font.setPixelSize(pixelSize);
    painter.setFont(font);
    painter.setPen(color);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(QChar(glyph)));

    return QIcon(pixmap);
}

CUKE_NAMESPACE_END(pub)