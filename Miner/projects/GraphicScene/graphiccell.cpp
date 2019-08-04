#include "GraphicScene/graphiccell.h"


gui::GraphicCell::GraphicCell(int row, int col, draw::ICellPainter* cell_painter,
                         quint8 width, quint8 height):
    Cell(row, col),
    m_cellPainter(cell_painter),
    m_width(width),
    m_height(height)
{

}

void gui::GraphicCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_cellPainter) {
        m_cellPainter->drawCell(painter, boundingRect(), opened());
        if (opened()) {
            if (mined()) {
                if (detonated())
                    m_cellPainter->drawMine(painter, boundingRect(), Qt::red);
                else
                    m_cellPainter->drawMine(painter, boundingRect());
            } else {
                if (!flagged())
                    m_cellPainter->drawColorDigit(painter, boundingRect(),digit() );
                else {
                    m_cellPainter->drawMine(painter, boundingRect());
                    m_cellPainter->drawCross(painter, boundingRect());
                }
            }
        } else {
            if (flagged())
               drawFlag(painter);
        }
    }
}

QRectF gui::GraphicCell::boundingRect() const
{
    return QRectF(col() * width(), row() * height(), width(), height());
}

void gui::GraphicCell::show()
{
    update();
}

quint8 gui::GraphicCell::width() const
{
    return m_width;
}

quint8 gui::GraphicCell::height() const
{
    return m_height;
}

draw::ICellPainter* gui::GraphicCell::cellPainter() const
{
    return m_cellPainter;
}

void gui::GraphicCell::drawFlag(QPainter* painter) const
{
    const int distance = 4;

    QRectF rect = boundingRect();
    int x = rect.x() + distance;
    int y = rect.y() + distance;
    int width = rect.width() - 2 * distance;
    int height = rect.height() - 2 * distance;

    if (m_cellPainter)
        m_cellPainter->drawFlag(painter, QRectF(x, y, width, height));
}


