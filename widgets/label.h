#ifndef LABEL_H
#define LABEL_H
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPainter>

#include "theme.h"
#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class LabelPrivate;
class WIDGETS_EXPORT Label : public QLabel {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(Label)
    TOMEER_Q_PROPERTY_DECL(QColor, TextColor)
    TOMEER_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit Label(QWidget *parent = nullptr);
    explicit Label(const QString &text, QWidget *parent = nullptr);
    explicit Label(const QString &text, const QColor &color, QWidget *parent = nullptr);
    ~Label() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END

#endif // LABEL_H
