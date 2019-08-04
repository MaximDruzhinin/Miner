#ifndef MINERCORE_H
#define MINERCORE_H

#include<QObject>
//include <QGraphicsView>
//#include "minescene.h"
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

namespace core {

class CORE_EXPORT Game: public QObject {
    Q_OBJECT
public:
    explicit Game(QObject* parent = 0);
    std::shared_ptr<MineField> run(GameType type);
    GameType type() const;
    QTime timeElapsed() const;
    virtual bool gameIsWin() const;
    virtual bool gameIsLost() const;
    GameStatus status() const;
    void setFactory(Factory* fact);

private:
    GameType m_type = GameType::Beginner;
    std::shared_ptr<MineField> m_minefield;
    QTime m_time;
    GameStatus m_status = GameStatus::NotStarted;
    int m_timeElapsed = 0;
    bool m_detonated = false;
    Factory* m_factory = nullptr;

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
