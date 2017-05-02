#include "guesswho.h"
#include "ui_guesswho.h"
#include "game.h"
#include "player.h"

#include <QSettings>
#include <QCloseEvent>
#include <QPushButton>

GuessWho::GuessWho(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuessWho)
    //, game(new Game(config, parent))
{
    ui->setupUi(this);
    QCoreApplication::setOrganizationName("linuxrelated");
    QCoreApplication::setOrganizationDomain("linuxrelated.de");
    QCoreApplication::setApplicationName("GuessWho");
    readSettings();
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
    for (int i = 0; i < game->getPlayers().size(); ++i) {
        QPushButton *playerButton = new QPushButton(this);
        Player* player = game->getPlayers()[i];
        playerButton->setText(player->getName());
        ui->playerButtons->addWidget(playerButton);
        connect(playerButton, &QPushButton::clicked, this, [i, playerButton, this]() {
            emit guessed(i);
        });
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

void GuessWho::on_nextButton_clicked()
{
    game->refreshImage();
}

void GuessWho::on_revealButton_clicked()
{
    game->revealImage();
}

void GuessWho::on_startButton_clicked()
{
    game->startSlideshow();
}

void GuessWho::on_stopButton_clicked()
{
    game->stopSlideshow();
}

void GuessWho::on_actionNewGame_triggered()
{
    if (game) {
        delete game;
    }
    game = new Game(config, parent());
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
