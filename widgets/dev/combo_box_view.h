#ifndef COMBO_BOX_VIEW_H
#define COMBO_BOX_VIEW_H
#include <QListView>
#include <QPainter>

#include "property.h"
#include "type.h"

TOMEER_NAMESPACE_BEGIN()
class ComboBoxView : public QListView {
    Q_OBJECT
public:
    explicit ComboBoxView(QWidget *parent = nullptr);
    ~ComboBoxView() override;

protected:
    int sizeHintForRow(int row) const override;
    virtual void onThemeChanged(ThemeType::ThemeMode mode);
};
TOMEER_NAMESPACE_END


#endif // COMBO_BOX_VIEW_H
