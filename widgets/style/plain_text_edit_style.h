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
};
TOMEER_NAMESPACE_END

#endif // PLAIN_TEXT_EDIT_STYLE_H