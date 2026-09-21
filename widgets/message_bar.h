#ifndef MESSAGE_BAR_H
#define MESSAGE_BAR_H
#include <QWidget>

#include "property.h"

TOMEER_NAMESPACE_BEGIN()
class MessageBarPrivate;
class WIDGETS_EXPORT MessageBar : public QWidget {
    Q_OBJECT
    TOMEER_DECLARE_DPTR(MessageBar)
public:
    explicit MessageBar(QWidget *parent = nullptr);
    ~MessageBar() override;
};
TOMEER_NAMESPACE_END

#endif // MESSAGE_BAR_H