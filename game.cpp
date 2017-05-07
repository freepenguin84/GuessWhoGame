#include "game.h"
#include <QPixmap>
#include <QImageReader>
#include <QDialog>
#include "pixelator.h"
#include "player.h"
#include "guessdialog.h"
#include "ui_gamewizard.h"

Game::Game(const Configuration &configuration, QObject *parent) : QObject(parent), config(configuration)
{
    connect(&timer, &QTimer::timeout, this, &Game::refreshImage);
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
    refreshImage();
}

void Game::refreshImage()
{
    if (pixelCountDown >= 0) {
        QPixmap pixelated = gw::Pixelator::doPixelate(currentImage, config.getSizes()[pixelCountDown--]);
        emit imageChanged(pixelated);
    } else {
        revealImage();
    }
}

void Game::startSlideshow()
{
    //timer.start(duration);
}

void Game::stopSlideshow()
{
    timer.stop();
}

void Game::revealImage()
{
    emit imageChanged(currentImage);
    currentScore = pixelCountDown + 2;
    pixelCountDown = 20;
    nextImage();
}

void Game::showWizard()
{
    QWizard gameWizard;
    wizardUi = new Ui::GameWizard;
    wizardUi->setupUi(&gameWizard);
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
        currentScore = 0;
    }
}

QList<Player *> Game::getPlayers() const
{
    return players;
}

void Game::nextImage()
{
    if (++currentImageIndex < fileNames.size()) {
        currentImage = getScaledImage(currentImageIndex);
    } else {
        currentImageIndex = -1;
        nextImage();
    }
}
