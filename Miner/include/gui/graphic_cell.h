#ifndef GRAPHICCELL_H
#define GRAPHICCELL_H

#include "core/cell.h"
#include "interfaces/ipainter.h"
#include <QGraphicsItem>
#include <memory>
#include "global/gui_global.h"

namespace gui {

class  GUI_EXPORT GraphicCell: public core::Cell, public QGraphicsItem {
public:
    GraphicCell(int row, int col, QObject* painter, uint width = 20, uint height = 20);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    QRectF boundingRect() const override;
    void changed() override;
    uint width() const;
    uint height() const;
    QObject* cellPainter() const;
private:
    QObject* m_painter = nullptr;
    uint m_width = 0;
    uint m_height = 0;
};

}

#endif // GRAPHICCELL_H
