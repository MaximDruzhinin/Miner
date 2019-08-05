#ifndef MINEFIELDSCENCE_H
#define MINEFIELDSCENCE_H

#include <QObject>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QGraphicsSceneMoveEvent>
#include <set>
#include "Core/minefield.h"
#include "Global/graphic_scene_global.h"

namespace gui {

class GRAPHICSCENE_EXPORT MineScene:  public QGraphicsScene, public core::MineField {
public:
    MineScene(quint8 rowCount = 9, quint8 colCount = 9, quint8 mineCount = 10, QObject* parent = 0);
    bool addCell(core::ICell* cell) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    quint8 cellWidth() const;
    quint8 cellHeight() const;
    void setView(QGraphicsView* view);

private:
    quint8 m_cellWidth;
    quint8 m_cellHeight;
    QGraphicsView* m_graphicsView = nullptr;
    bool m_firstClick = true;
};
}

#endif // MINEFIELDSCENE_H
