#ifndef COMBOBOX_H
#define COMBOBOX_H
#include <QComboBox>
#include <QObject>
#include <QPainter>
#include <QAbstractItemView>
#include <QPropertyAnimation>
#include <QApplication>
#include <QLayout>
#include <QGraphicseffect>

#include "ContextMixin.h"
#include "Property.h"

CUKE_BEGIN_NAMESPACE(widget)
class ComboBoxPrivate;
class CUKE_EXPORT ComboBox : public ContextMixin<QComboBox> {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ComboBox)
    CUKE_Q_PROPERTY_DECL(int, RotateAngle)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(int, PopupHeight)
public:
    explicit ComboBox(QWidget *parent = nullptr);
    ~ComboBox() override;

protected:
    void showPopup() override;
    void hidePopup() override;
    void paintEvent(QPaintEvent *event) override;
};
CUKE_END_NAMESPACE(widget)

#endif //COMBOBOX_H
