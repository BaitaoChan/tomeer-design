#include <QPainter>
#include "icon.h"
TOMEER_NAMESPACE_BEGIN()
TOMEER_Q_SINGLETON_IMPL(Icon)
Icon::Icon(QObject *parent)
    : QObject(parent) {
}

Icon::~Icon() = default;

QIcon Icon::getIcon(IconType::Icon glyph) {
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform);

    QFont font("tomeer");
    font.setPixelSize(32);
    painter.setFont(font);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(QChar(glyph)));

    return QIcon(pixmap);
}

QIcon Icon::getIcon(IconType::Icon glyph, QColor color) {
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform);

    QFont font("tomeer");
    font.setPixelSize(32);
    painter.setFont(font);
    painter.setPen(color);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(QChar(glyph)));

    return QIcon(pixmap);
}

QIcon Icon::getIcon(IconType::Icon glyph, QColor color, int pixelSize) {
    QPixmap pixmap(pixelSize, pixelSize);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing
                           | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform);

    QFont font("tomeer");
    font.setPixelSize(pixelSize);
    painter.setFont(font);
    painter.setPen(color);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, QString(QChar(glyph)));

    return QIcon(pixmap);
}

TOMEER_NAMESPACE_END