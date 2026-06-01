#ifndef CUKECOMBOBOXVIEW_H
#define CUKECOMBOBOXVIEW_H
#include <QListView>
#include <QPainter>

#include "CukeObjectMap.h"
#include "CukeProperty.h"
#include "CukeType.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeComboBoxView : public QListView {
    Q_OBJECT
public:
    explicit CukeComboBoxView(QWidget *parent = nullptr);
    ~CukeComboBoxView() override;

protected:
    int sizeHintForRow(int row) const override;
    virtual void onThemeChanged(CukeThemeType::ThemeMode mode);
};
CUKE_NAMESPACE_END(pub)


#endif // CUKECOMBOBOXVIEW_H
