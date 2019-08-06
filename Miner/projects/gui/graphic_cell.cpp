#include "gui/graphic_cell.h"
#include <qdebug.h>

gui::GraphicCell::GraphicCell(int row, int col, QObject* painter,
                         uint width, uint height):
    Cell(row, col),
    m_painter(painter),
    m_width(width),
    m_height(height)
{
}

void gui::GraphicCell::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    if (m_painter) {
        draw::ICellPainter* myPainter = dynamic_cast<draw::ICellPainter*>(m_painter);
        if (!myPainter) {
            qDebug () << "Can't cast to draw::IPainter";
            return;
        }
        myPainter->drawCell(painter, boundingRect(), opened());
        if (opened()) {
            if (mined()) {
                if (detonated())
                    myPainter->drawMine(painter, boundingRect(), Qt::red);
                else
                    myPainter->drawMine(painter, boundingRect());
            } else {
                if (!flagged())
                    myPainter->drawColorDigit(painter, boundingRect(), digit() );
                else {
                    myPainter->drawMine(painter, boundingRect());
                    myPainter->drawCross(painter, boundingRect());
                }
            }
        } else {
            if (flagged()) {
                myPainter->drawFlag(painter, boundingRect());
            }
        }
    }
}

QRectF gui::GraphicCell::boundingRect() const
{
    return QRectF(col() * width(), row() * height(), width(), height());
}

void gui::GraphicCell::changed()
{
    update();
}

uint gui::GraphicCell::width() const
{
    return m_width;
}

uint gui::GraphicCell::height() const
{
    return m_height;
}

QObject* gui::GraphicCell::cellPainter() const
{
    return m_painter;
}



