#ifndef CUKEMENUBAR_H
#define CUKEMENUBAR_H
#include <QMenuBar>

#include "CukeContext.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenuBarPrivate;
class CUKE_EXPORT CukeMenuBar : public QMenuBar, public CukeContext {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeMenuBar)
public:
    explicit CukeMenuBar(QWidget* parent = nullptr);
    ~CukeMenuBar() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUBAR_H
