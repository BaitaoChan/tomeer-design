#ifndef CUKEICON_H
#define CUKEICON_H
#include <QIcon>

#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(widget)
class CUKE_EXPORT CukeIcon : public QObject {
    Q_OBJECT
    CUKE_Q_SINGLETON_IMPL(CukeIcon)
private:
    explicit CukeIcon(QObject *parent = nullptr);
    ~CukeIcon() override;
public:

};

CUKE_NAMESPACE_END(widget)

#endif // CUKEICON_H
