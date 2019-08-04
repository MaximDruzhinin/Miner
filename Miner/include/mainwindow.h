#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "GraphicScene/minescene.h"
#include "Core/minercore.h"
//#include "miner.h"
#include <memory>

class QTimer;
class QTime;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    gui::MineScene* m_mineField;
    QTimer* m_timer;
    //core::Game* m_miner = nullptr;
    std::shared_ptr<core::Game> m_miner;
    QStatusBar* m_statusBar;
    void updateStatusBar();
    //core::MineField* m_minefield = nullptr;
    std::shared_ptr<core::MineField> m_minefield;
    bool runGame(GameType type);

private slots:
    void onFlagSetted();
    void onFlagRemoved();
    void on_timeout();
    void onGameIsWin();
    void on_action_exit_triggered();
    void on_action_beginner_triggered();
    void on_action_medium_triggered();
    void on_action_expert_triggered();
};

#endif // MAINWINDOW_H
