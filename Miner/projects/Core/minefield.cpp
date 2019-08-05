#include <queue>

#include "Core/minefield.h"
#include "Core/cell.h"

core::MineField::MineField(quint8 rowCount, quint8 colCount, quint8 mineCount, QObject* parent):
    QObject(parent),
    m_rowCount(rowCount),
    m_colCount(colCount),
    m_mineCount(mineCount)
{
    m_cells.resize(rowCount);

    for (auto i = 0; i < rowCount; i++)
        m_cells[i].resize(colCount);
}

bool core::MineField::addCell(ICell* cell)
{
    if (!cell)
        return false;

    auto row = cell->row();
    auto col = cell->col();
    m_cells[row][col] = cell;

    return true;

}

bool core::MineField::addFlagInCell(int row, int col)
{
    if (!isInit())
        return false;

    auto cell = at(row, col);
    if (!cell)
        return false;

    if (m_flagCells.size() >= m_mineCount)
        return false;

    if (cell->setFlag()) {
        m_flagCells.insert(cell);
        if (cell->mined()) {
            m_revealedMineCount++;
        }
        emit flagSetted();

        return true;
    }

    return false;
}

bool core::MineField::removeFlagFromCell(int row, int col)
{
    ICell* cell = at(row, col);
    if (!cell)
        return false;

    if (cell->removeFlag()) {
        //auto pos = qFind(m_flagCells.begin(), m_flagCells.end(), cell);
        auto pos = std::find(m_flagCells.begin(), m_flagCells.end(), cell);
        if (pos != m_flagCells.end()) {
            m_flagCells.erase(pos);
            if (cell->mined())
                m_revealedMineCount--;
            emit flagRemoved();
            return true;
        }
//        else
//            return false;
    }
    //else
    return false;

}

core::ICell* core::MineField::at(int row, int col) const
{
    if (!outOfRange(row, col))
        return m_cells[row][col];

    return nullptr;
}

bool core::MineField::outOfRange(int row, int col) const
{
    return (row < 0 || col < 0 || col > m_colCount - 1 || row > m_rowCount - 1);
}

quint8 core::MineField::rowCount() const
{
    return m_rowCount;
}

quint8 core::MineField::colCount() const
{
    return m_colCount;
}

quint8 core::MineField::mineCount() const
{
    return m_mineCount;
}


void core::MineField::init(ICell* cell)
{
    if (m_isInit)
        return;

    if (!m_colCount || !m_rowCount) {
        m_isInit = false;
        return;
    }

    cell->open(true);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    std::vector<int> numbers(m_colCount* m_rowCount, 0);
    for (auto i = 0; i < numbers.size(); i++)
        numbers[i] = i;

    for (auto i = 0; i < m_mineCount;) {
        int r = rand() % (numbers.size()-1-i) + i;
        int col = numbers[r] / m_rowCount;
        int row = numbers[r] % m_rowCount;

        auto cell = m_cells[row][col];
        if (!cell->opened()) {
            std::swap(numbers[i], numbers[r]);
            i++;
            auto object = dynamic_cast<core::Cell*>(cell);
            if (object)
                QObject::connect(object, SIGNAL(detonation()), this, SLOT(on_detonation_cell()));

            cell->setMine();
            m_mineCells.insert(cell);
            changeDigitInNeibCells(cell);
        }
    }
    m_isInit = true;

    emit on_initialized();
}

void core::MineField::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

bool core::MineField::enabled() const
{
    return m_enabled;
}

void core::MineField::openCell(ICell* cell)
{
    if (cell->flagged())
        return;

    if (!isInit())
        return;

    std::queue<ICell*> q;
    if (!cell->opened()) {
        if (!cell->empty())
            cell->open(true);
        else {
            cell->setReadyOpen(true);
            q.push(cell);
        }
    }
    do {
        if (!q.empty()) {
            cell = q.front();
            q.pop();
            cell->open(true);
        }
        if (cell->empty()) {
            const auto& neibs = neibCells(cell->row(), cell->col());
            if (!neibs.empty()) {
                for (auto cell: neibs) {
                    if (!cell->readyOpened() && cell->empty()) {
                        cell->setReadyOpen(true);
                        q.push(cell);
                    }
                    if (!cell->empty() && !cell->flagged())
                        cell->open(true);
                }
            }
        }
    }
    while (!q.empty());
}

void core::MineField::openUnrevealedMines()
{
    for (auto cell: m_mineCells) {
        if (!cell->opened() && !cell->flagged())
            cell->open(false);
    }
}

void core::MineField::openIncorrectFlagged()
{
    for (auto cell: m_flagCells) {
        if (!cell->mined())
            cell->open(true);
    }
}

size_t core::MineField::flagCount() const
{
    return m_flagCells.size();
}

size_t core::MineField::revealedMineCount() const
{
    return m_revealedMineCount;
}

bool core::MineField::isInit() const
{
    return m_isInit;
}

void core::MineField::on_detonation_cell()
{
    emit detonationCell();
}

void core::MineField::changeDigitInNeibCells(ICell* cell)
{
   const auto& neibs = neibCells(cell->row(), cell->col());

   for (auto cell : neibs) {
       auto digit = cell->digit();
       cell->setDigit(++digit);
   }
}

std::set<core::ICell*> core::MineField::neibCells(int row, int col) const
{
    std::set<ICell*> neibs;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++ ) {
            if (i || j) {
                auto neib = at(row + i, col + j);
                if (neib)
                    neibs.insert(neib);
            }
        }
    }
    return neibs;
}




