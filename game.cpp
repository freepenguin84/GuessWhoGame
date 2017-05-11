#include "game.h"
#include <QPixmap>
#include <QImageReader>
#include <QDialog>
#include <QPushButton>
#include "pixelator.h"
#include "player.h"
#include "guessdialog.h"
#include "ui_gamewizard.h"

Game::Game(const Configuration &configuration, QObject *parent) : QObject(parent), config(configuration)
{
    connect(&timer, &QTimer::timeout, this, &Game::showNextPixelated);
}

QPixmap Game::getScaledImage(const int index) const
{
    QImageReader ir(fileNames[index]);
    ir.setAutoTransform(true);
    QPixmap image { QPixmap::fromImageReader(&ir) };
    return image.scaled(config.getImageWidth(), config.getImageHeight(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void Game::start()
{
    currentImage = getScaledImage(0);
    showNextPixelated();
    emit uiChanged(false);
}

void Game::showNextPixelated()
{
    if (pixelCountDown >= 0) {
        QPixmap pixelated = gw::Pixelator::doPixelate(currentImage, config.getSizes()[pixelCountDown--]);
        emit imageChanged(pixelated);
    } else {
        pixelCountDown = 0;
        currentScore = 0;
        revealImage();
    }
}

void Game::startSlideshow()
{
    timer.start(config.getDuration());
}

void Game::stopSlideshow()
{
    timer.stop();
}

void Game::revealImage()
{
    emit imageChanged(currentImage);
    emit uiChanged(true);
    currentScore = pixelCountDown + 2;
    pixelCountDown = 20;
    loadNextImage();
}

void Game::showWizard()
{
    QWizard gameWizard;
    wizardUi = new Ui::GameWizard;
    wizardUi->setupUi(&gameWizard);
    wizardUi->imagesPage->setTitle("Images");
    wizardUi->playersPage->setTitle("Players");
    if (gameWizard.exec()) {
        fileNames = gameWizard.field("imageFiles").value<QStringList>();
        for (int i = 0; i < wizardUi->playersPage->getPlayerCount(); ++i) {
            players += new Player(gameWizard.field(QString("player") + QString::number(i)).toString());
        }
        emit wizardCompleted();
    }
    delete wizardUi;
}

void Game::showGuessDialog(int player)
{
    GuessDialog dialog(currentScore);
    if (dialog.exec()) {
        players[player]->addGuess(dialog.getMulti(), currentScore, "");
        emit guessCompleted(player);
        emit uiChanged(false);
        currentScore = 0;
    }
}

QList<Player *> Game::getPlayers() const
{
    return players;
}

void Game::loadNextImage()
{
    if (++currentImageIndex < fileNames.size()) {
        currentImage = getScaledImage(currentImageIndex);
    } else {
        currentImageIndex = -1;
        loadNextImage();
    }
}
