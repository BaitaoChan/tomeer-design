#ifndef CUKEMENUBAR_H
#define CUKEMENUBAR_H
#include <QMenuBar>

#include "CukeScope.h"
#include "CukeProperty.h"

CUKE_NAMESPACE_BEGIN(pub)
class CukeMenuBarPrivate;
class CUKE_EXPORT CukeMenuBar : public QMenuBar, public CukeScope {
    Q_OBJECT
    CUKE_DECLARE_DPTR(CukeMenuBar)
public:
    explicit CukeMenuBar(QWidget* parent = nullptr);
    ~CukeMenuBar() override;
};
CUKE_NAMESPACE_END(pub)

#endif // CUKEMENUBAR_H
