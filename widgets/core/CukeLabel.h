#ifndef CUKELABEL_H
#define CUKELABEL_H
#include <QLabel>
#include <QColor>
#include <QFont>
#include <QPainter>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class LabelPrivate;
class CUKE_EXPORT Label : public QLabel {
    Q_OBJECT
    CUKE_DECLARE_DPTR(Label)
    CUKE_Q_PROPERTY_DECL(QColor, TextColor)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit Label(QWidget *parent = nullptr);
    explicit Label(const QString &text, QWidget *parent = nullptr);
    explicit Label(const QString &text, const QColor &color, QWidget *parent = nullptr);
    ~Label() override;

protected:
    void paintEvent(QPaintEvent *event) override;

    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // CUKELABEL_H