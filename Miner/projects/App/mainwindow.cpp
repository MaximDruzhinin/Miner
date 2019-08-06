#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gui/graphic_cell.h"
#include "draw/painter.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QStatusBar>
#include "gui/factory.h"
#include "logger.h"
#include "draw/painter.h"


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_statusBar = new QStatusBar;
    setStatusBar(m_statusBar);

    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);
    m_statusBar->setGeometry(0, 0, 0, 20);

    m_miner = std::make_shared<Miner>(ui->graphicsView, parent);

    if (!m_miner->runGame(GameType::Beginner)) {
        LOG_ERROR("Game not started");
        return;
    }
    resizeWindow();

    updateStatusBar();

    m_timer = new QTimer(parent);
    m_timer->start(100);

    connect(m_miner.get(), SIGNAL(on_flagSetted()), this, SLOT(onFlagSetted()));
    connect(m_miner.get(), SIGNAL(on_gameIsWin()), this, SLOT(onGameIsWin()));
    connect(m_miner.get(), SIGNAL(on_flagRemoved()), this, SLOT(onFlagRemoved()));
    connect(m_miner.get(), SIGNAL(timeout()), this, SLOT(onMinerTimeout()));
    connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_statusBar;
}

void MainWindow::updateStatusBar()
{
    QString text;
    uint flags = m_miner->flagCount();
    uint mines = m_miner->mineCount();
    QTime time = m_miner->timeElapsed();
    text = QString("Мины: %1 / %2   Время  %3").arg(flags).arg(mines).arg(time.toString("mm:ss"));
    m_statusBar->showMessage(text);
}

void MainWindow::resizeWindow()
{
    const QRectF& rect = ui->graphicsView->geometry();
    setFixedSize(QSize(rect.width(), rect.height() + m_statusBar->height() + menuBar()->height()+ ui->mainToolBar->height()));
}

void MainWindow::onFlagSetted()
{
    updateStatusBar();
}

void MainWindow::onFlagRemoved()
{
    updateStatusBar();
}

void MainWindow::on_timeout()
{
    updateStatusBar();
}

void MainWindow::onGameIsWin()
{
    QMessageBox::information(this, "", "Игра пройдена!");
}

void MainWindow::on_action_beginner_triggered()
{
    if (m_miner->runGame(GameType::Beginner))
        resizeWindow();
}

void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::on_action_medium_triggered()
{
    if (m_miner->runGame(GameType::Medium))
        resizeWindow();
}

void MainWindow::on_action_expert_triggered()
{
    if (m_miner->runGame(GameType::Expert))
        resizeWindow();
}

void MainWindow::onMinerTimeout()
{
    updateStatusBar();
}
