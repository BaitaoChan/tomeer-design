#ifndef PLAIN_TEXT_EDIT_STYLE_H
#define PLAIN_TEXT_EDIT_STYLE_H
#include <QProxyStyle>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class PlainTextEditStyle : public QProxyStyle {
    Q_OBJECT
public:
    explicit PlainTextEditStyle(QStyle *style = nullptr);
    ~PlainTextEditStyle() override;

    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget = nullptr) const override;
    void polish(QWidget *widget) override;
};
TOMEER_NAMESPACE_END

#endif // PLAIN_TEXT_EDIT_STYLE_H
