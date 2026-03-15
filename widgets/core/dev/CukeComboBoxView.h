#ifndef CUKECOMBOBOXVIEW_H
#define CUKECOMBOBOXVIEW_H
#include <QListView>
#include <QPainter>

#include "CukeContextMixin.h"

CUKE_NAMESPACE_BEGIN(widget)
class CukeComboBoxView : public CukeContextMixin<QListView> {
    Q_OBJECT
public:
    explicit CukeComboBoxView(QWidget *parent = nullptr);
    ~CukeComboBoxView() override;

protected:
    int sizeHintForRow(int row) const override;
    void onThemeChanged(CukeThemeType::ThemeMode mode) override;
};
CUKE_NAMESPACE_END(widget)


#endif // CUKECOMBOBOXVIEW_H
