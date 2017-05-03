#include "guesswho.h"
#include "ui_guesswho.h"
#include "game.h"
#include "player.h"

#include <QSettings>
#include <QCloseEvent>
#include <QHBoxLayout>

GuessWho::GuessWho(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuessWho)
{
    ui->setupUi(this);
    QCoreApplication::setOrganizationName("linuxrelated");
    QCoreApplication::setOrganizationDomain("linuxrelated.de");
    QCoreApplication::setApplicationName("GuessWho");
    readSettings();
    QTimer::singleShot(0, this, &GuessWho::on_actionNewGame_triggered);
}

GuessWho::~GuessWho()
{
    delete ui;
    delete game;
}

void GuessWho::refreshImage(const QPixmap &image)
{
    ui->imageLabel->setPixmap(image);
}

void GuessWho::showPlayerButtons()
{
    for (int i = 0; i < ui->playerButtons->count(); ++i) {
        QPushButton* button = qobject_cast<QPushButton*>(ui->playerButtons->itemAt(i)->widget());
        connect(button, &QPushButton::clicked, this, [i, this]() {
            emit guessed(i);
        });
        button->setEnabled(i < game->getPlayers().size());
    }
    game->start();
}

void GuessWho::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

void GuessWho::readSettings()
{
    QSettings settings;
    settings.beginGroup("GuessWho");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
    config.readSettings(settings);
}

void GuessWho::writeSettings()
{
    QSettings settings;
    settings.beginGroup("GuessWho");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
    config.writeSettings(settings);
}

void GuessWho::on_actionNewGame_triggered()
{
    if (game) {
        delete game;
    }
    game = new Game(config, parent());

    connect(ui->nextButton, &QPushButton::clicked, game, &Game::refreshImage);
    connect(ui->revealButton, &QPushButton::clicked, game, &Game::revealImage);
    connect(ui->startButton, &QPushButton::clicked, game, &Game::startSlideshow);
    connect(ui->stopButton, &QPushButton::clicked, game, &Game::stopSlideshow);

    connect(game, &Game::imageChanged, this, &GuessWho::refreshImage);
    connect(game, &Game::wizardCompleted, this, &GuessWho::showPlayerButtons);
    connect(this, &GuessWho::guessed, game, &Game::showGuessDialog);

    game->showWizard();
}

void GuessWho::on_actionFullscreen_triggered()
{
    ui->imageLabel->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    ui->imageLabel->showFullScreen();
}

void GuessWho::on_actionSettings_triggered()
{
    config.showDialog();
}
