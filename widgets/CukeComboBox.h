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

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class ComboBoxPrivate;
class CUKE_EXPORT ComboBox : public QComboBox {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ComboBox)
    CUKE_Q_PROPERTY_DECL(int, RotateAngle)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(int, PopupHeight)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ComboBox(QWidget *parent = nullptr);
    ~ComboBox() override;

protected:
    void showPopup() override;
    void hidePopup() override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END

#endif // CUKECOMBOBOX_H