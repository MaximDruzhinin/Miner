#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "GraphicScene/minescene.h"
#include "Core/minercore.h"
#include "GraphicScene/miner.h"
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QTimer* m_timer;
    std::shared_ptr<Miner> m_miner;
    QStatusBar* m_statusBar;
    void updateStatusBar();
    void resizeWindow();
private slots:
    void onFlagSetted();
    void onFlagRemoved();
    void on_timeout();
    void onGameIsWin();
    void on_action_exit_triggered();
    void on_action_beginner_triggered();
    void on_action_medium_triggered();
    void on_action_expert_triggered();
    void onMinerTimeout();
};

#endif // MAINWINDOW_H
