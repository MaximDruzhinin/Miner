#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GraphicScene/graphiccell.h"
#include "Draw/cellpainter.h"
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QStatusBar>
#include <GraphicScene/factory.h>
#include "logger.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_statusBar = new QStatusBar;
    setStatusBar(m_statusBar);

    ui->graphicsView->setAlignment(Qt::AlignLeft|Qt::AlignTop);

    m_miner = std::make_shared<core::Game>(nullptr);
    m_miner->setFactory(new gui::Factory);

    if (!runGame(GameType::Beginner)) {
        LOG_ERROR("Game not started");
        return;
    }

    m_timer = new QTimer;
    m_timer->start();

    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    QObject::connect(m_miner.get(), SIGNAL(on_flagSetted()), this, SLOT(onFlagSetted()));
    QObject::connect(m_miner.get(), SIGNAL(on_gameIsWin()), this, SLOT(onGameIsWin()));
    QObject::connect(m_miner.get(), SIGNAL(on_flagRemoved()), this, SLOT(onFlagRemoved()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_statusBar;
    delete m_timer;
}

void MainWindow::updateStatusBar()
{
    if (!m_minefield) {
        LOG_ERROR("m_minefield is null");
        return;
    }

    QString text;
    auto flags = m_minefield->flagCount();
    auto mines = m_minefield->mineCount();
    QTime time = m_miner->timeElapsed();
    text = QString("Мины: %1 / %2   Время  %3").arg(flags).arg(mines).arg(time.toString("mm:ss"));
    m_statusBar->showMessage(text);
}

bool MainWindow::runGame(GameType type)
{
    m_minefield = m_miner->run(type);
    if (!m_minefield) {
        LOG_ERROR("Failed init minefield")
        return false;
    }
    std::shared_ptr<gui::MineScene> scene = std::dynamic_pointer_cast<gui::MineScene>(m_minefield);
    if (!scene) {
        LOG_ERROR("Can't cast to gui::MineScene")
        return false;
    }
    scene->setView(ui->graphicsView);
    return true;
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
    if (!runGame(GameType::Beginner)) {
        LOG_ERROR("Game not started");
        return;
    }
}

void MainWindow::on_action_exit_triggered()
{
    close();
}

void MainWindow::on_action_medium_triggered()
{
   if (!runGame(GameType::Medium))
       LOG_ERROR("Game not started");
}

void MainWindow::on_action_expert_triggered()
{
   if (!runGame(GameType::Expert))
       LOG_ERROR("Game not started");
}
