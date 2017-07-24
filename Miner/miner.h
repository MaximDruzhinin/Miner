#ifndef MINER_H
#define MINER_H

#include "minercore.h"

namespace game {

    class Miner : public MinerCore
    {
    public:
        Miner(QGraphicsView* graphics_view, QWidget *parent = 0);
    private:
        QGraphicsView* m_graphicsView = nullptr;
    protected:
        base::MineField* createMineField(qint8 rowCount, qint8 colCount, quint16 mineCount) override;

    };

}

#endif // MINER_H
