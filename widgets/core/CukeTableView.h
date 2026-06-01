#ifndef TABLEVIEW_H
#define TABLEVIEW_H
#include <QTableView>
#include <QPropertyAnimation>
#include <QHeaderView>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeTableViewPrivate;
class CUKE_EXPORT CukeTableView : public QTableView {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeTableView)
    CUKE_Q_PROPERTY_DECL(CukeThemeType::ThemeMode, ThemeMode)
public:
    explicit CukeTableView(QWidget *parent = nullptr);
    ~CukeTableView() override;

protected:
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)

#endif // TABLEVIEW_H
