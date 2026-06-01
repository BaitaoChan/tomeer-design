#ifndef CUKEWINDOWPRIVATE_H
#define CUKEWINDOWPRIVATE_H
#include "CukeProperty.h"
#include "CukeType.h"

class QVBoxLayout;
class QMainWindow;
CUKE_NAMESPACE_BEGIN(pub)
class CukeAppBar;
class CukeWindow;
class CukeWindowPrivate : public QObject {
    Q_OBJECT
    CUKE_DECLARE_QPTR(CukeWindow)
    CUKE_Q_PROPERTY_DECL(bool, IsResize)
    CUKE_Q_PROPERTY_DECL(bool, IsDrag)
public:
    explicit CukeWindowPrivate(CukeWindow *q = nullptr);
    ~CukeWindowPrivate() override;

private:
    CukeAppBar *_appBar = nullptr;

    void *_widget = nullptr;

    CukeThemeType::ThemeMode _themeMode = CukeThemeType::Dark;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEWINDOWPRIVATE_H
