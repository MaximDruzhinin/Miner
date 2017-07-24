#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphiccell.h"
#include "cellpainter.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QStatusBar>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    status_bar_ = new QStatusBar;
    setStatusBar(status_bar_);

    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_miner = new game::Miner(ui->graphicsView);
    m_miner->startNewGame(GameType::beginner);

    m_timer = new QTimer;
    m_timer->start();

    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    QObject::connect(m_miner, SIGNAL(on_flagSetted()), this, SLOT(on_miner_flagSetted()));
    QObject::connect(m_miner, SIGNAL(on_gameIsWin()), this, SLOT(on_miner_gameIsWin()));
    QObject::connect(m_miner, SIGNAL(on_flagRemoved()), this, SLOT(on_miner_flagRemoved()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete status_bar_;
    delete m_timer;
}

void MainWindow::updateStatusBar()
{
    QString text;
    auto flags = m_miner->minefield()->flagCount();
    auto mines = m_miner->minefield()->mineCount();
    QTime time = m_miner->timeElapsed();
    text = QString("Мины: %1 / %2   Время  %3").arg(flags).arg(mines).arg(time.toString("mm:ss"));
    status_bar_->showMessage(text);
}

void MainWindow::on_miner_flagSetted()
{
    updateStatusBar();
}

void MainWindow::on_miner_flagRemoved()
{
    updateStatusBar();
}

void MainWindow::on_timeout()
{
    updateStatusBar();
}

void MainWindow::on_miner_gameIsWin()
{
    QMessageBox::information(this, "", "Игра пройдена!");
}

void MainWindow::on_action_beginner_triggered()
{
    m_miner->startNewGame(GameType::beginner);
}

void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::on_action_medium_triggered()
{
   m_miner->startNewGame(GameType::medium);
}

void MainWindow::on_action_expert_triggered()
{
   m_miner->startNewGame(GameType::expert);
}
