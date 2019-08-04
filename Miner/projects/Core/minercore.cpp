#include "Core/minercore.h"
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
        colCount = 9;
        rowCount = 9;
        mineCount = 10;
        break;
    case GameType::Medium:
        colCount = 16;
        rowCount = 16;
        mineCount = 40;
        break;
    case GameType::Expert:
        colCount = 30;
        rowCount = 16;
        mineCount = 99;
        break;
    }

    if (!m_factory) {
        LOG_ERROR("factory not init")
        return nullptr;
    }
    m_minefield = m_factory->createMineField(rowCount, colCount, mineCount);
    if (!m_minefield) {
        LOG_ERROR("Failed to create minefield")
        return nullptr;
    }

    if (m_minefield) {
        QObject::connect(m_minefield.get(), SIGNAL(on_initialized()), this, SLOT(on_minefield_initalized()));
        QObject::connect(m_minefield.get(), SIGNAL(flagSetted()), this, SLOT(on_minefield_flagSetted()));
        QObject::connect(m_minefield.get(), SIGNAL(flagRemoved()),this, SLOT(on_minefield_flagRemoved()));
        QObject::connect(m_minefield.get(), SIGNAL(detonationCell()), this, SLOT(on_minefield_detonationCell()));
    }

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
    return (m_minefield->revealedMineCount() == m_minefield->mineCount());
}

bool core::Game::gameIsLost() const
{
    return m_detonated;
}


GameStatus core::Game::status() const
{
    return m_status;
}

void core::Game::setFactory(Factory* fact)
{
    m_factory = fact;
}

void core::Game::on_minefield_initalized()
{
    m_time.start();
    m_status = GameStatus::Running;
}

void core::Game::on_minefield_flagSetted()
{
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
