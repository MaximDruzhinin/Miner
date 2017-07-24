#ifndef MINEFIELDSCENCE_H
#define MINEFIELDSCENCE_H

#include <QGraphicsScene>
#include "icell.h"
#include <QtCore>
#include <QtGui>
#include <QGraphicsSceneMoveEvent>
#include <set>
#include "minefield.h"

namespace gui
{
    class MineScene: public QGraphicsScene, public base::MineField
    {
    public:
        MineScene(quint8 rowCount = 9, quint8 colCount = 9, quint8 mineCount = 10, QObject* parent = 0);
        bool addCell(base::ICell* cell) override;
        void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
        quint8 cellWidth() const;
        quint8 cellHeight() const;

    private:
        quint8 m_cellWidth;
        quint8 m_cellHeight;
    };

}

#endif // MINEFIELDSCENE_H
