#ifndef MINERCORE_H
#define MINERCORE_H

#include<QObject>
#include <QTime>
#include <memory>
#include "Global/core_global.h"
#include "Core/minefield.h"
#include <Core/factory_core.h>

enum class GameType {
    Beginner,
    Medium,
    Expert
};

enum class GameStatus {
    NotStarted,
    Running,
    IsOver,
    Passed
 };


struct Presets {
    static const int BEGINNER_COL_COUNT = 9;
    static const int BEGINNER_ROW_COUNT = 9;
    static const int BEGINNER_MINE_COUNT = 10;

    static const int MEDIUM_COL_COUNT = 16;
    static const int MEDIUM_ROW_COUNT = 16;
    static const int MEDIUM_MINE_COUNT = 40;

    static const int EXPERT_COL_COUNT = 30;
    static const int EXPERT_ROW_COUNT = 16;
    static const int EXPERT_MINE_COUNT = 99;
};



namespace core {

class CORE_EXPORT Game: public QObject {
    Q_OBJECT
public:
    explicit Game(QObject* parent = nullptr);
    std::shared_ptr<MineField> run(GameType type);
    GameType type() const;
    QTime timeElapsed() const;
    virtual bool gameIsWin() const;
    virtual bool gameIsLost() const;
    GameStatus status() const;
    void setFactory(std::shared_ptr<Factory> fact);

private:
    GameType m_type = GameType::Beginner;
    std::shared_ptr<MineField> m_minefield;
    QTime m_time;
    GameStatus m_status = GameStatus::NotStarted;
    int m_timeElapsed = 0;
    bool m_detonated = false;
    std::shared_ptr<Factory> m_factory;

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
