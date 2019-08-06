#ifndef GRAPHIC_CELL_H
#define GRAPHIC_CELL_H

#include <qobject.h>

namespace gui {
class IGraphicCell {
public:
    virtual ~IGraphicCell()  {}
    virtual void show() = 0;
    virtual void setPainter(QObject* painer);
};

}

#endif // GRAPHIC_CELL_H
