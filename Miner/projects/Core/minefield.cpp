#include <queue>
#include "core/minefield.h"
#include "core/cell.h"

core::MineField::MineField(uint rowCount, uint colCount, uint mineCount, QObject* parent):
    QObject(parent),
    m_rowCount(rowCount),
    m_colCount(colCount),
    m_mineCount(mineCount)
{
    m_cells.resize(rowCount);

    for (uint i = 0; i < rowCount; i++)
        m_cells[i].resize(colCount);
}

bool core::MineField::addCell(ICell* cell)
{
    if (!cell)
        return false;

    uint row = cell->row();
    uint col = cell->col();
    m_cells[row][col] = cell;

    return true;
}

bool core::MineField::addFlagInCell(int row, int col)
{
    if (!isInit())
        return false;

    auto cell = at(row, col);
    Q_ASSERT(cell);

    if (m_flagCells.size() >= m_mineCount)
        return false;

    if (cell->setFlag()) {
        m_flagCells.push_back(cell);
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
    Q_ASSERT(cell);

    if (cell->removeFlag()) {
        auto pos = std::find(m_flagCells.begin(), m_flagCells.end(), cell);
        if (pos != m_flagCells.end()) {
            m_flagCells.erase(pos);
            if (cell->mined())
                m_revealedMineCount--;
            emit flagRemoved();
            return true;
        }
    }

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
    return (row < 0 || col < 0 || col > static_cast<int>(m_colCount) - 1 || row > static_cast<int>(m_rowCount) - 1);
}

uint core::MineField::rowCount() const
{
    return m_rowCount;
}

uint core::MineField::colCount() const
{
    return m_colCount;
}

uint core::MineField::mineCount() const
{
    return m_mineCount;
}

//генерация мин перестановками
void core::MineField::init(ICell* cell)
{
    if (m_isInit)
        return;

    if (!m_colCount || !m_rowCount) {
        m_isInit = false;
        return;
    }

    Q_ASSERT(m_mineCount < m_colCount * m_rowCount - 1);

    cell->open(true);

    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));

    std::vector<uint> numbers(m_colCount * m_rowCount, 0);
    for (std::size_t i = 0; i < numbers.size(); i++)
        numbers[i] = static_cast<uint>(i);

    for (uint i = 0; i < m_mineCount;) {
        uint r = rand() % (numbers.size() - 1 - i) + i;
        uint col = numbers[r] / m_rowCount;
        uint row = numbers[r] % m_rowCount;

        auto cell = m_cells[row][col];
        if (!cell->opened()) {
            std::swap(numbers[i], numbers[r]);
            i++;
            core::Cell* qcell = dynamic_cast<core::Cell*>(cell);
            Q_ASSERT(qcell);
            QObject::connect(qcell, SIGNAL(detonation()), this, SLOT(on_detonation_cell()));
            cell->setMine();
            m_mineCells.push_back(cell);
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

//При открытии пустой клетки, должны рекурсивно открываться ее пустые соседи, однако рекурсия может сломать стек,
// поэтому реализация будет через очередь
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

uint core::MineField::flagCount() const
{
    return static_cast<uint>(m_flagCells.size());
}

uint core::MineField::revealedMineCount() const
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
       int digit = cell->digit();
       cell->setDigit(++digit);
   }
}

std::vector<core::ICell*> core::MineField::neibCells(uint row, uint col) const
{
    std::vector<ICell*> neibs;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++ ) {
            if (i || j) {
                core::ICell* neib = at(static_cast<int>(row) + i, static_cast<int>(col) + j);
                if (neib)
                    neibs.push_back(neib);
            }
        }
    }
    return neibs;
}




