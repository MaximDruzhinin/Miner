#ifndef GRAPHICCELL_H
#define GRAPHICCELL_H

#include "Core/cell.h"
#include "Draw/icellpainter.h"
#include <QGraphicsItem>
#include <memory>
#include "Global/graphic_scene_global.h"

namespace gui {
    class  GRAPHICSCENE_EXPORT GraphicCell: public core::Cell, public QGraphicsItem {
    public:
        GraphicCell(int row, int col, draw::ICellPainter* cellPainter,
                    quint8 width = 20, quint8 height = 20);

        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
        QRectF boundingRect() const override;
        void show() override;
        quint8 width() const;
        quint8 height() const;
        draw::ICellPainter* cellPainter() const;

    private:
        void drawFlag(QPainter* painter) const;
        draw::ICellPainter* m_cellPainter;
        quint8 m_width;
        quint8 m_height;

    };

}

#endif // GRAPHICCELL_H