#ifndef MINER_H
#define MINER_H

#include "Core/minercore.h"
#include <qgraphicsview.h>
#include "Global/graphic_scene_global.h"
#include <GraphicScene/factory.h>


class GRAPHICSCENE_EXPORT Miner : public core::Game {
    Q_OBJECT
public:
    Miner(QGraphicsView* view, QObject* parent = nullptr);
    bool runGame(GameType type);
    uint flagCount();
    uint mineCount();
private:
    QObject* m_painter = nullptr;
    std::shared_ptr<core::MineField> m_minefield;
    QGraphicsView* m_view = nullptr;
signals:
    void timeout();
private slots:
    void onTimeout();

};


#endif // MINER_H
