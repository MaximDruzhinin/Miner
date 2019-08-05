#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QObject>

//#include <QGraphicsScene>
#include "icell.h"
#include <QtCore>
#include <QtGui>
//#include <QGraphicsSceneMoveEvent>
#include <set>
#include <memory>
#include <QVector>

#include "Global/core_global.h"

class ICellPainter;

namespace core {

class CORE_EXPORT MineField : public QObject {
    Q_OBJECT
public:
    MineField(quint8 rowCount = 9, quint8 colCount = 9, quint8 mineCount = 10, QObject* parent = 0);
    virtual bool addCell(ICell* cell);
    bool addFlagInCell(int row, int col);
    bool removeFlagFromCell(int row, int col);
    ICell* at(int row, int col) const;
    bool outOfRange(int row, int col) const;
    quint8 rowCount() const;
    quint8 colCount() const;
    quint8 mineCount() const;
    void init(ICell* cell);
    void setEnabled(bool enabled);
    bool enabled() const;
    void openCell(ICell* cell);
    void openUnrevealedMines();
    void openIncorrectFlagged();
    size_t flagCount() const;
    size_t revealedMineCount() const;
    bool isInit() const;

signals:
    void flagSetted() ;
    void flagRemoved();
    void on_initialized();
    void detonationCell();

public slots:
    void on_detonation_cell();

private:
    void changeDigitInNeibCells(ICell* cell);
    std::set<ICell*> neibCells(int row, int col) const;
    quint8 m_rowCount;
    quint8 m_colCount;
    quint8 m_mineCount;
    bool m_isInit = false;
    bool m_enabled = true;
    std::vector<std::vector<ICell*>> m_cells;
    std::set<ICell*> m_mineCells;
    std::set<ICell*> m_flagCells;
    quint8 m_revealedMineCount = 0;
};

}

#endif // MINEFIELD_H
