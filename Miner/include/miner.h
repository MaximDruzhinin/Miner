#ifndef MINER_H
#define MINER_H

#include "Core/minercore.h"
#include <qgraphicsview.h>
#include "Global/graphic_scene_global.h"
#include <GraphicScene/factory.h>

namespace game {

    class GRAPHICSCENE_EXPORT Miner : public MinerCore
    {
    public:
        //Miner(QGraphicsView* graphics_view, QWidget *parent = 0);
        Miner(base::Factory* fact);
    private:
        //QGraphicsView* m_graphicsView = nullptr;
        base::Factory* m_fact = nullptr;
    protected:
        //base::MineField* createMineField(qint8 rowCount, qint8 colCount, quint16 mineCount) override;

    };

}

#endif // MINER_H
