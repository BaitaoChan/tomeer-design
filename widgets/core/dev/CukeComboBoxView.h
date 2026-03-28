#ifndef CUKECOMBOBOXVIEW_H
#define CUKECOMBOBOXVIEW_H
#include <QListView>
#include <QPainter>

#include "CukeScope.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeComboBoxView : public QListView, public CukeScope {
    Q_OBJECT
public:
    explicit CukeComboBoxView(QWidget *parent = nullptr);
    ~CukeComboBoxView() override;

protected:
    int sizeHintForRow(int row) const override;
    void onThemeChanged(CukeThemeType::ThemeMode mode) override;
};
CUKE_NAMESPACE_END(pub)


#endif // CUKECOMBOBOXVIEW_H
