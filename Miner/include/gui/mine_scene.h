#ifndef MINEFIELDSCENCE_H
#define MINEFIELDSCENCE_H

#include <QObject>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QGraphicsSceneMoveEvent>
#include <set>
#include "core/minefield.h"
#include "global/gui_global.h"

namespace gui {

class GRAPHICSCENE_EXPORT MineScene:  public QGraphicsScene, public core::MineField {
public:
    MineScene(uint rowCount = 9, uint colCount = 9, uint mineCount = 10, QObject* parent = nullptr);
    bool addCell(core::ICell* cell) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void setView(QGraphicsView* view);
private:
    QGraphicsView* m_graphicsView = nullptr;
    bool m_firstClick = true;
};
}

#endif // MINEFIELDSCENE_H
