#include "minercore.h"
#include "minescene.h"
#include "graphiccell.h"
#include "cellpainter.h"
#include <QMessageBox>

game::MinerCore::MinerCore(QWidget *parent): QObject(parent),
    m_time(0,0,0)
{

}

void game::MinerCore::startNewGame(GameType type)
{
    m_gameType = type;
    m_gameStatus = GameStatus::notStarted;

    quint16 colCount, rowCount, mineCount;
    switch (type)
    {
    case GameType::beginner:
        colCount = 9;
        rowCount = 9;
        mineCount = 10;
        break;
    case GameType::medium:
        colCount = 16;
        rowCount = 16;
        mineCount = 40;
        break;
    case GameType::expert:
        colCount = 30;
        rowCount = 16;
        mineCount = 99;
        break;
    }
    m_minefield = createMineField(rowCount, colCount, mineCount);

    auto minefield = dynamic_cast<base::MineField*>(m_minefield);
    if (minefield)
    {
        QObject::connect(minefield, SIGNAL(on_initialized()), this, SLOT(on_minefield_initalized()));
        QObject::connect(minefield, SIGNAL(flagSetted()), this, SLOT(on_minefield_flagSetted()));
        QObject::connect(minefield, SIGNAL(flagRemoved()),this, SLOT(on_minefield_flagRemoved()));
        QObject::connect(minefield, SIGNAL(detonationCell()), this, SLOT(on_minefield_detonationCell()));
    }
}

GameType game::MinerCore::gameType() const
{
    return m_gameType;
}


QTime game::MinerCore::timeElapsed() const
{
    QTime time(0,0,0);

    switch (m_gameStatus)
    {
    case GameStatus::notStarted:
        return time;
    case GameStatus::playing:
        return time.addMSecs(m_time.elapsed());
    case GameStatus::losing:
    case GameStatus::winning:
        return time.addMSecs(time_elapsed_);
    }
    return time;
}

bool game::MinerCore::gameIsWin() const
{
    return (m_minefield->mineCountRevealed() == m_minefield->mineCount());
}

bool game::MinerCore::gameIsLost() const
{
    return m_detonationCount > 0;
}

base::MineField* game::MinerCore::minefield()
{
    return m_minefield;
}

GameStatus game::MinerCore::gameStatus() const
{
    return m_gameStatus;
}


void game::MinerCore::on_minefield_initalized()
{
    m_time.start();
    m_gameStatus = GameStatus::playing;
}

void game::MinerCore::on_minefield_flagSetted()
{
    emit on_flagSetted();

    if (gameIsWin())
    {
        m_minefield->setEnabled(false);
        m_gameStatus = GameStatus::winning;
        time_elapsed_ = m_time.elapsed();
        emit on_gameIsWin();
    }
}

void game::MinerCore::on_minefield_flagRemoved()
{
    emit on_flagRemoved();
}

void game::MinerCore::on_minefield_detonationCell()
{
    m_detonationCount++;
    if (gameIsLost())
    {
        m_minefield->setEnabled(false);
        m_minefield->openUnrevealedMines();
        m_minefield->openIncorrectRevealedMines();
        time_elapsed_ = m_time.elapsed();
        m_gameStatus = GameStatus::losing;
        emit on_gameIsLost();
    }
}
