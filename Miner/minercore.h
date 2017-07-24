#ifndef MINERCORE_H
#define MINERCORE_H

#include<QObject>
#include <QGraphicsView>
#include "minescene.h"
#include <QTime>
#include <memory>

class QGraphicsScene;


enum class GameType
{
    beginner,
    medium,
    expert
};

enum class GameStatus
{
    notStarted,
    playing,
    losing,
    winning
 };

namespace game {

    class MinerCore: public QObject
    {
        Q_OBJECT
    public:
        explicit MinerCore(QWidget* parent = 0);
        void startNewGame(GameType type);
        GameType gameType() const;
        QTime timeElapsed() const;
        virtual bool gameIsWin() const;
        virtual bool gameIsLost() const;
        base::MineField* minefield();
        GameStatus gameStatus() const;

    private:
        GameType m_gameType = GameType::beginner;
        QGraphicsView* m_graphicsView = nullptr;
        base::MineField* m_minefield;
        QTime m_time;
        GameStatus m_gameStatus = GameStatus::notStarted;
        int time_elapsed_ = 0;
        int m_detonationCount = 0;

    protected:
         virtual base::MineField* createMineField(qint8 rowCount, qint8 colCount, quint16 mineCount) = 0; // создать минное поле

    signals:
         void on_gameIsWin();
         void on_gameIsLost();
         void on_flagSetted();
         void on_flagRemoved();

    private slots:
        void on_minefield_initalized();
        void on_minefield_flagSetted();
        void on_minefield_flagRemoved();
        void on_minefield_detonationCell();

    };
}

#endif // MINERCORE_H
