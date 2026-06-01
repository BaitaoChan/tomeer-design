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

CUKE_NAMESPACE_BEGIN(pub)
class CukeComboBoxPrivate;
class CUKE_EXPORT CukeComboBox : public QComboBox {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeComboBox)
    CUKE_Q_PROPERTY_DECL(int, RotateAngle)
    CUKE_Q_PROPERTY_DECL(int, LineHalfWidth)
    CUKE_Q_PROPERTY_DECL(int, BorderRadius)
    CUKE_Q_PROPERTY_DECL(int, PopupHeight)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeComboBox(QWidget *parent = nullptr);
    ~CukeComboBox() override;

protected:
    void showPopup() override;
    void hidePopup() override;
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKECOMBOBOX_H
