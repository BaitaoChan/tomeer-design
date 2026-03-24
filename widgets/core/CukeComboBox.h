#ifndef CUKECOMBOBOX_H
#define CUKECOMBOBOX_H
#include <QComboBox>
#include <QObject>
#include <QPainter>
#include <QAbstractItemView>
#include <QPropertyAnimation>
#include <QApplication>
#include <QLayout>
#include <QGraphicseffect>

#include "CukeContext.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeComboBoxPrivate;
class CUKE_EXPORT CukeComboBox : public QComboBox, public CukeContext {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeComboBox)
    CUKE_Q_PROPERTY_DECL(int, RotateAngle)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(int, PopupHeight)
public:
    explicit CukeComboBox(QWidget *parent = nullptr);
    ~CukeComboBox() override;

protected:
    void showPopup() override;
    void hidePopup() override;
    void paintEvent(QPaintEvent *event) override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECOMBOBOX_H
