#ifndef CUKECOMBOBOXVIEW_H
#define CUKECOMBOBOXVIEW_H
#include <QListView>
#include <QPainter>

#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class ComboBoxView : public QListView {
    Q_OBJECT
public:
    explicit ComboBoxView(QWidget *parent = nullptr);
    ~ComboBoxView() override;

protected:
    int sizeHintForRow(int row) const override;
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)


#endif // CUKECOMBOBOXVIEW_H
