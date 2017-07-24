#include "miner.h"
#include "graphiccell.h"
#include "cellpainter.h"
#include <QDebug>





game::Miner::Miner(QGraphicsView *graphicsView, QWidget* parent): MinerCore(parent),
    m_graphicsView(graphicsView)
{

}

base::MineField* game::Miner::createMineField(qint8 rowCount, qint8 colCount, quint16 mineCount)
{
    const int cellWidth = 20;
    const int cellHeight = 20;

    base::MineField* minefield = new gui::MineScene(rowCount, colCount, mineCount);
    m_graphicsView->setScene(dynamic_cast<gui::MineScene*>(minefield));

    for (auto i = 0; i < rowCount; i++)
    {
        for (auto j = 0; j < colCount; j++)
            minefield->addCell(new base::GraphicCell(i,j, new draw::CellPainter, cellWidth, cellHeight));
    }

    m_graphicsView->setGeometry(0,0, cellWidth * colCount + 1, cellHeight * rowCount + 1);

    return minefield;
}
