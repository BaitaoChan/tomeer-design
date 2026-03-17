#ifndef CUKEAPPLICATION_H
#define CUKEAPPLICATION_H
#include <QObject>

#include "CukeProperty.h"

#define cApp CukeApplication::instance()

CUKE_NAMESPACE_BEGIN(widget)
class CUKE_EXPORT CukeApplication : public QObject {
    Q_OBJECT
    CUKE_Q_SINGLETON_DECL(CukeApplication)
private:
    explicit CukeApplication(QObject *parent = nullptr);
    ~CukeApplication() override;
public:
    void init();
};
CUKE_NAMESPACE_END(widget)

#endif // CUKEAPPLICATION_H
