#ifndef TOOL_TIP_H
#define TOOL_TIP_H
#include <QWidget>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ToolTipPrivate;
class WIDGETS_EXPORT ToolTip : public QWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ToolTip)
    TOMEER_Q_PROPERTY_DECL(QString, ToolTip)
public:
    explicit ToolTip(QWidget *parent = nullptr);
    ~ToolTip() override;

    static void showText(const QPoint &pos, const QString &text, QWidget *widget = nullptr);
    static void hideText();

protected:
    void paintEvent(QPaintEvent *event) override;
};
TOMEER_NAMESPACE_END

#endif // TOOL_TIP_H
