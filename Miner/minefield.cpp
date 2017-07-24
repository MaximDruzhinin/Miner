//#include "minefieldscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <graphiccell.h>
#include <QGraphicsItem>
#include <QMessageBox>
#include <queue>

#include "cellpainter.h"
#include "minefield.h"



base::MineField::MineField(quint8 rowCount, quint8 colCount, quint8 mineCount, QObject* parent):
    QObject(parent),
    m_rowCount(rowCount),
    m_colCount(colCount),
    m_mineCount(mineCount)
{
    m_cells.resize(rowCount);

    for (auto i = 0; i < rowCount; i++)
        m_cells[i].resize(colCount);
}

bool base::MineField::addCell(ICell *cell)
{
    if (!cell)
        return false;

    auto row = cell->row();
    auto col = cell->col();
    m_cells[row][col] = cell;

    return true;

}

bool base::MineField::addFlagInCell(int row, int col)
{
    if (m_firstTimeOpen)
        return false;

    ICell* cell = at(row, col);
    if (!cell)
        return false;

    if (m_flagCells.size() >= m_mineCount)
        return false;

    if (cell->setFlag())
    {
        m_flagCells.insert(cell);
        if (cell->mined()) {
            m_mineCountRevealed++;
        }
        emit flagSetted();

        return true;
    }

    return false;
}

bool base::MineField::removeFlagFromCell(int row, int col)
{
    ICell* cell = at(row, col);
    if (!cell)
        return false;

    if (cell->removeFlag())
    {
        auto pos = qFind(m_flagCells.begin(), m_flagCells.end(), cell);
        if (pos != m_flagCells.end())
        {
            m_flagCells.erase(pos);
            if (cell->mined())
                m_mineCountRevealed--;
            emit flagRemoved();
            return true;
        }
        else
            return false;
    }
    else
        return false;

}

base::ICell* base::MineField::at(int row, int col) const
{
    if (!outOfRange(row, col))
        return m_cells[row][col];

    return nullptr;
}

bool base::MineField::outOfRange(int row, int col) const
{
    return (row < 0 || col < 0 || col > m_colCount-1 || row > m_rowCount-1);
}

quint8 base::MineField::rowCount() const
{
    return m_rowCount;
}

quint8 base::MineField::colCount() const
{
    return m_colCount;
}

quint8 base::MineField::mineCount() const
{
    return m_mineCount;
}


void base::MineField::init()
{
    if (m_initialized)
        return;

    if (!m_colCount || !m_rowCount)
    {
        m_initialized = false;
        return;
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QVector<int> numbers(m_colCount* m_rowCount, 0);
    for (auto i = 0; i < numbers.size(); i++)
        numbers[i] = i;

    for (auto i = 0; i < m_mineCount;)
    {
        int k = rand()%(numbers.size()-1-i) + i;
        int col = numbers[k] / m_rowCount;
        int row = numbers[k] % m_rowCount;

        ICell* cell = m_cells[row][col];
        if (!cell->opened())
        {
            qSwap(numbers[i], numbers[k]);
            i++;
            auto object = dynamic_cast<Cell*>(cell);
            if (object)
                QObject::connect(object, SIGNAL(detonation()), this, SLOT(on_detonation_cell()));

            cell->setMine();
            m_mineCells.insert(cell);
            changeDigitInNeibCells(cell);
        }
    }
    m_initialized = true;
    emit on_initialized();
}

bool base::MineField::initialized() const
{
    return m_initialized;
}

void base::MineField::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool base::MineField::enabled() const
{
    return m_enabled;
}


void base::MineField::openCell(ICell *cell)
{
    if (cell->flagged())
        return;


    if (m_firstTimeOpen)
    {
        cell->open(true);
        init();
        m_firstTimeOpen = false;
    }
    QQueue<ICell*> q;
    if (!cell->opened())
    {
        if (!cell->empty())
            cell->open(true);
        else
        {
            cell->setReadyOpen(true);
            q.push_back(cell);
        }
    }
    do
    {
        if (!q.empty())
        {
            cell = q.front();
            q.pop_front();
            cell->open(true);
        }
        if (cell->empty())
        {
            const auto& neibs = neibCells(cell->row(), cell->col());
            if (!neibs.empty())
            {
                for (auto cell: neibs)
                {
                    if (!cell->readyOpened() && cell->empty())
                    {
                        cell->setReadyOpen(true);
                        q.push_back(cell);
                    }
                    if (!cell->empty() && !cell->flagged())
                        cell->open(true);
                }
            }
        }
    }
    while (!q.empty());

}

void base::MineField::openUnrevealedMines()
{
    for (auto cell: m_mineCells)
    {
        if (!cell->opened() && !cell->flagged())
            cell->open(false);
    }
}

void base::MineField::openIncorrectRevealedMines()
{
    for (auto cell: m_flagCells)
    {
        if (!cell->mined())
            cell->open(true);
    }
}

size_t base::MineField::flagCount() const
{
    return m_flagCells.size();
}

size_t base::MineField::mineCountRevealed() const
{
    return m_mineCountRevealed;
}

void base::MineField::on_detonation_cell()
{
    emit detonationCell();
}


void base::MineField::changeDigitInNeibCells(ICell *cell)
{
   const auto& neibs = neibCells(cell->row(), cell->col());

   for (auto cell : neibs)
   {
       auto digit = cell->digit();
       cell->setDigit(++digit);
   }
}

QSet<base::ICell*> base::MineField::neibCells(int row, int col) const
{
    QSet<ICell*> neibs;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++ )
        {
            if (i || j)
            {
                ICell* neib = at(row+i, col+j);
                if (neib)
                    neibs.insert(neib);
            }
        }
    }
    return neibs;
}




