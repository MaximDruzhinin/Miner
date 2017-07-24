#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <minescene.h>
#include <minercore.h>
#include <miner.h>
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
    game::MinerCore* m_miner;
    QStatusBar* status_bar_;
    void updateStatusBar();

private slots:
    void on_miner_flagSetted();
    void on_miner_flagRemoved();
    void on_timeout();
    void on_miner_gameIsWin();
    void on_action_exit_triggered();
    void on_action_beginner_triggered();
    void on_action_medium_triggered();
    void on_action_expert_triggered();
};

#endif // MAINWINDOW_H
