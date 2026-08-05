#ifndef CUKEAPPLICATION_H
#define CUKEAPPLICATION_H
#include <QObject>

#include "CukeProperty.h"

#define CUKE_APP Application::instance()

CUKE_NAMESPACE_BEGIN()
class CUKE_EXPORT Application : public QObject {
    Q_OBJECT
    CUKE_Q_SINGLETON_DECL(Application)
private:
    explicit Application(QObject *parent = nullptr);
    ~Application() override;
public:
    void init();
};
CUKE_NAMESPACE_END

#endif // CUKEAPPLICATION_H