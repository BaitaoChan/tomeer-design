#ifndef COMBOBOXVIEW_H
#define COMBOBOXVIEW_H
#include <QListView>
#include <QPainter>

#include "ContextMixin.h"

CUKE_BEGIN_NAMESPACE(widget)
class ComboBoxView : public ContextMixin<QListView> {
    Q_OBJECT
public:
    explicit ComboBoxView(QWidget *parent = nullptr);
    ~ComboBoxView() override;

protected:
    int sizeHintForRow(int row) const override;
    void onThemeChanged(ThemeType::Mode mode) override;
};
CUKE_END_NAMESPACE(widget)


#endif // COMBOBOXVIEW_H
