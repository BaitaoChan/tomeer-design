#ifndef COMBO_BOX_H
#define COMBO_BOX_H
#include <QComboBox>
#include <QObject>
#include <QPainter>
#include <QAbstractItemView>
#include <QPropertyAnimation>
#include <QApplication>
#include <QLayout>
#include <QGraphicseffect>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class ComboBoxPrivate;
class WIDGETS_EXPORT ComboBox : public QComboBox {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(ComboBox)
    TOMEER_Q_PROPERTY_DECL(int, RotateAngle)
    TOMEER_Q_PROPERTY_DECL(int, LineHalfWidth)
    TOMEER_Q_PROPERTY_DECL(int, BorderRadius)
    TOMEER_Q_PROPERTY_DECL(int, PopupHeight)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ComboBox(QWidget *parent = nullptr);
    ~ComboBox() override;

protected:
    void showPopup() override;
    void hidePopup() override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // COMBO_BOX_H