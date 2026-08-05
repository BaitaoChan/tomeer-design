#ifndef CUKESCROLLBAR_H
#define CUKESCROLLBAR_H
#include <QScrollBar>

#include "CukeTheme.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN()
class ScrollBarPrivate;
class CUKE_EXPORT ScrollBar : public QScrollBar {
    Q_OBJECT
    CUKE_DECLARE_DPTR(ScrollBar)
    CUKE_Q_PROPERTY_DECL(ThemeType::ThemeMode, ThemeMode)
public:
    explicit ScrollBar(QWidget *parent = nullptr);
    explicit ScrollBar(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~ScrollBar() override;

protected:
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END

#endif // CUKESCROLLBAR_H