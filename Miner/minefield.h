#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QObject>

#include <QGraphicsScene>
#include "icell.h"
#include <QtCore>
#include <QtGui>
#include <QGraphicsSceneMoveEvent>
#include <set>
#include <memory>
#include <QVector>


class ICellPainter;

namespace base {

    class MineField : public QObject
    {
        Q_OBJECT
    public:
        MineField(quint8 rowCount = 9, quint8 colCount = 9, quint8 mineCount = 10, QObject* parent = 0);
        virtual bool addCell(base::ICell* cell);
        bool addFlagInCell(int row, int col);
        bool removeFlagFromCell(int row, int col);
        ICell* at(int row, int col) const;
        bool outOfRange(int row, int col) const;
        quint8 rowCount() const;
        quint8 colCount() const;
        quint8 mineCount() const;
        void init();
        bool initialized() const;
        void setEnabled(bool enabled);
        bool enabled() const;
        void openCell(ICell* cell);
        void openUnrevealedMines();
        void openIncorrectRevealedMines();
        size_t flagCount() const;
        size_t mineCountRevealed() const;
    signals:
        void flagSetted() ;
        void flagRemoved();
        void on_initialized();
        void detonationCell();
    public slots:
        void on_detonation_cell();
    private:
        void changeDigitInNeibCells(base::ICell* cell);
        QSet<base::ICell*> neibCells(int row, int col) const;
        quint8 m_rowCount;
        quint8 m_colCount;
        quint8 m_mineCount;
        bool m_initialized = false;
        bool m_enabled = true;
        QVector<QVector<base::ICell*>> m_cells;
        QSet<base::ICell*> m_mineCells;
        QSet<base::ICell*> m_flagCells;
        quint8 m_mineCountRevealed = 0;
        bool m_firstTimeOpen = true;
    };

}

#endif // MINEFIELD_H
