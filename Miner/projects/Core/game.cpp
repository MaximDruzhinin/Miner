#include "core/game.h"
#include "logger.h"

core::Game::Game(QObject* parent): QObject(parent), m_time(0,0,0)
{
}

std::shared_ptr<core::MineField> core::Game::run(GameType type)
{
    m_type = type;
    m_status = GameStatus::NotStarted;

    int colCount, rowCount, mineCount;

    switch (type){
    case GameType::Beginner:
        colCount = Presets::BEGINNER_COL_COUNT;
        rowCount = Presets::BEGINNER_ROW_COUNT;
        mineCount = Presets::BEGINNER_MINE_COUNT;
        break;
    case GameType::Medium:
        colCount = Presets::MEDIUM_COL_COUNT;
        rowCount = Presets::MEDIUM_ROW_COUNT;
        mineCount = Presets::MEDIUM_MINE_COUNT;
        break;
    case GameType::Expert:
        colCount = Presets::EXPERT_COL_COUNT;
        rowCount = Presets::EXPERT_ROW_COUNT;
        mineCount = Presets::EXPERT_MINE_COUNT;
        break;
    }

    Q_ASSERT(m_factory);

    m_minefield = m_factory->createMineField(rowCount, colCount, mineCount);

    Q_ASSERT(m_minefield);

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            m_minefield->addCell(m_factory->createCell(i, j));
        }
    }

    QObject::connect(m_minefield.get(), SIGNAL(on_initialized()), this, SLOT(on_minefield_initalized()));
    QObject::connect(m_minefield.get(), SIGNAL(flagSetted()),     this, SLOT(on_minefield_flagSetted()));
    QObject::connect(m_minefield.get(), SIGNAL(flagRemoved()),    this, SLOT(on_minefield_flagRemoved()));
    QObject::connect(m_minefield.get(), SIGNAL(detonationCell()), this, SLOT(on_minefield_detonationCell()));

    return m_minefield;
}

GameType core::Game::type() const
{
    return m_type;
}

QTime core::Game::timeElapsed() const
{
    QTime time(0,0,0);

    switch (m_status) {
    case GameStatus::NotStarted:
        return time;
    case GameStatus::Running:
        return time.addMSecs(m_time.elapsed());
    case GameStatus::IsOver:
    case GameStatus::Passed:
        return time.addMSecs(m_timeElapsed);
    }

    return time;
}

bool core::Game::gameIsWin() const
{
    return (m_minefield ? m_minefield->revealedMineCount() == m_minefield->mineCount() : false);
}

bool core::Game::gameIsLost() const
{
    return m_detonated;
}

GameStatus core::Game::status() const
{
    return m_status;
}

void core::Game::setFactory(std::shared_ptr<core::Factory> factory)
{
    m_factory = factory;
}

void core::Game::on_minefield_initalized()
{
    m_time.start();
    m_status = GameStatus::Running;
}

void core::Game::on_minefield_flagSetted()
{
    Q_ASSERT(m_minefield);

    emit on_flagSetted();

    if (gameIsWin()) {
        m_minefield->setEnabled(false);
        m_status = GameStatus::Passed;
        m_timeElapsed = m_time.elapsed();
        emit on_gameIsWin();
    }
}

void core::Game::on_minefield_flagRemoved()
{
    emit on_flagRemoved();
}

void core::Game::on_minefield_detonationCell()
{
    Q_ASSERT(m_minefield);

    m_detonated = true;

    if (gameIsLost()) {
        m_minefield->setEnabled(false);
        m_minefield->openUnrevealedMines();
        m_minefield->openIncorrectFlagged();
        m_timeElapsed = m_time.elapsed();
        m_status = GameStatus::IsOver;
        emit on_gameIsLost();
    }
}
