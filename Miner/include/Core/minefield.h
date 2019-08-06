#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <qobject.h>
#include "icell.h"
#include <QtCore>
#include <QtGui>
#include <set>
#include <memory>
#include <QVector>
#include "global/core_global.h"

class ICellPainter;

namespace core {

class CORE_EXPORT MineField : public QObject {
    Q_OBJECT
public:
    MineField(uint rowCount = 9, uint colCount = 9, uint mineCount = 10, QObject* parent = nullptr);
    virtual bool addCell(ICell* cell);
    bool addFlagInCell(int row, int col);
    bool removeFlagFromCell(int row, int col);
    ICell* at(int row, int col) const;
    bool outOfRange(int row, int col) const;
    uint rowCount() const;
    uint colCount() const;
    uint mineCount() const;
    void init(ICell* cell);
    void setEnabled(bool enabled);
    bool enabled() const;
    void openCell(ICell* cell);
    void openUnrevealedMines();
    void openIncorrectFlagged();
    uint flagCount() const;
    uint revealedMineCount() const;
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
    std::set<ICell*> neibCells(uint row, uint col) const;
    uint m_rowCount = 0;
    uint m_colCount = 0;
    uint m_mineCount = 0;
    bool m_isInit = false;
    bool m_enabled = true;
    std::vector<std::vector<ICell*>> m_cells;
    std::set<ICell*> m_mineCells;
    std::set<ICell*> m_flagCells;
    uint m_revealedMineCount = 0;
};

}

#endif // MINEFIELD_H
