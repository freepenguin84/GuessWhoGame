#include "guesswho.h"
#include "ui_guesswho.h"
#include "game.h"
#include "player.h"
#include "playerinfo.h"

#include <QSettings>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QPushButton>
#include <QAction>

GuessWho::GuessWho(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GuessWho)
{
    ui->setupUi(this);
    ui->infoWidget->setVisible(false);
    QCoreApplication::setOrganizationName("linuxrelated");
    QCoreApplication::setOrganizationDomain("linuxrelated.de");
    QCoreApplication::setApplicationName("GuessWho");
    readSettings();
    QTimer::singleShot(0, this, &GuessWho::on_actionNewGame_triggered);
    pixelCountLabel = new QLabel;
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

void GuessWho::updateInfo(const int playerIndex)
{
    infos[playerIndex]->update();
    togglePlayerButtons(false);
    on_nextButton_clicked();
}

void GuessWho::showPlayerButtons()
{
    auto players = game->getPlayers();
    for (int i = 0; i < players.size(); ++i) {
        // buttons
        auto button = new QPushButton(players[i]->getName(), this);
        button->setShortcut(tr("" + i + 1));
        buttons += button;
        ui->playerButtons->insertWidget(i, button);
        connect(button, &QPushButton::clicked, this, [i, this]() {
            emit guessed(i);
        });

        // infos
        auto info = new PlayerInfo(players[i], this);
        info->update();
        infos += info;
        auto layout = qobject_cast<QVBoxLayout*>(ui->infoWidget->layout());
        layout->addWidget(info);
        layout->addStretch();
    }
    ui->actionToggleControls->setChecked(true);
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

void GuessWho::connectUI()
{
    //connect(ui->revealButton, &QPushButton::clicked, game, &Game::revealImage);

    connect(game, &Game::imageChanged, this, &GuessWho::refreshImage);
    connect(game, &Game::wizardCompleted, this, &GuessWho::showPlayerButtons);
    connect(game, &Game::guessCompleted, this, &GuessWho::updateInfo);
    connect(game, &Game::uiChanged, this, &GuessWho::togglePlayerButtons);
    connect(this, &GuessWho::guessed, game, &Game::showGuessDialog);
}

void GuessWho::togglePlayerButtons(bool enabled)
{
    for (auto button : buttons) {
        button->setEnabled(enabled);
    }
}

void GuessWho::on_actionNewGame_triggered()
{
    ui->actionToggleControls->toggled(false);
    if (game) {
        delete game;
    }
    game = new Game(config, parent());
    connectUI();
    game->showWizard();
}

void GuessWho::on_actionSettings_triggered()
{
    config.showDialog();
}

void GuessWho::on_showScoreButton_toggled()
{
    auto layout = ui->imageLayout;
    QLayoutItem* item = layout->itemAt(1);
    auto widget = item->widget();
    widget->setVisible(ui->showScoreButton->isChecked());
}

void GuessWho::on_actionToggleControls_toggled(bool checked)
{
    ui->controlWidget->setVisible(checked);
}

void GuessWho::on_toggleShowButton_toggled()
{
    if (ui->toggleShowButton->isChecked()) {
        game->startSlideshow();
        togglePlayerButtons(false);
        ui->toggleShowButton->setText(tr("Stop Slideshow"));
        ui->nextButton->setEnabled(false);
        ui->revealButton->setEnabled(false);
    } else {
        game->stopSlideshow();
        ui->toggleShowButton->setText(tr("Start Slideshow"));
        ui->nextButton->setEnabled(true);
        ui->revealButton->setEnabled(true);
    }
}

void GuessWho::on_nextButton_clicked()
{
    game->showNextPixelated();
    togglePlayerButtons(false);
    ui->revealButton->setEnabled(true);
}

void GuessWho::on_revealButton_clicked()
{
    game->revealImage();
    ui->revealButton->setEnabled(false);
}
