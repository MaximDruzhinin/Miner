#include "miner.h"
#include "GraphicScene/graphiccell.h"
#include "Draw/cellpainter.h"
#include <QDebug>
#include <GraphicScene/minescene.h>
#include <qgraphicsview.h>
#include <GraphicScene/factory.h>



//game::Miner::Miner(QGraphicsView *graphicsView, QWidget* parent): MinerCore(nullptr),
//    m_graphicsView(graphicsView)
//{

//}

game::Miner::Miner(base::Factory* fact): MinerCore(nullptr), m_fact(fact)
{

}

//base::MineField* game::Miner::createMineField(qint8 rowCount, qint8 colCount, quint16 mineCount)
//{
//    const int cellWidth = 20;
//    const int cellHeight = 20;

//    if (!m_fact) {
//        qDebug () << "Dsdsdsdsds==========";
//        return nullptr;
//    }
//    base::MineField* minefield= m_fact->createMineField(rowCount, colCount, mineCount);


//    return minefield;
//}
