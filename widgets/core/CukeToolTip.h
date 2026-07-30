#ifndef CUKETOOLTIP_H
#define CUKETOOLTIP_H
#include <QWidget>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class ToolTipPrivate;
class CUKE_EXPORT ToolTip : public QWidget {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ToolTip)
    CUKE_Q_PROPERTY_DECL(QString, ToolTip)
public:
    explicit ToolTip(QWidget *parent = nullptr);
    ~ToolTip() override;

    static void showText(const QPoint &pos, const QString &text, QWidget *widget = nullptr);
    static void hideText();

protected:
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKETOOLTIP_H