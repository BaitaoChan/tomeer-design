#ifndef APPLICATION_H
#define APPLICATION_H
#include <QObject>

#include "property.h"

#define TOMEER_APP Application::instance()

TOMEER_NAMESPACE_BEGIN()
class WIDGETS_EXPORT Application : public QObject {
    Q_OBJECT
    TOMEER_Q_SINGLETON_DECL(Application)
private:
    explicit Application(QObject *parent = nullptr);
    ~Application() override;
public:
    void init();
};
TOMEER_NAMESPACE_END

#endif // APPLICATION_H
