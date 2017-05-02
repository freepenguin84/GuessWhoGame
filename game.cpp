#include "game.h"
#include <QPixmap>
#include <QImageReader>
#include <QDialog>
#include "pixelator.h"
#include "player.h"
#include "gamewizard.h"
#include "guessdialog.h"

Game::Game(const Configuration &configuration, QObject *parent) : QObject(parent), config(configuration)
{
    connect(&timer, &QTimer::timeout, this, &Game::refreshImage);
}

void Game::setFileNames(QStringList value)
{
    fileNames = value;
}

void Game::addPlayer(QString name)
{
    players.append(new Player(name));
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
    pixelCountDown = 20;
    nextImage();
}

void Game::showWizard()
{
    GameWizard gameWizard;
    if (gameWizard.exec()) {
        QStringList fileNames = gameWizard.field("imageFiles").value<QStringList>();
        setFileNames(fileNames);
        for (int i = 0; i < gameWizard.playerCount(); ++i) {
            addPlayer(gameWizard.field(QString("player") + QString::number(i)).toString());
        }
        emit wizardCompleted();
    }

}

void Game::showGuessDialog(int player)
{
    int score = pixelCountDown + 2;
    GuessDialog dialog(score);
    if (dialog.exec()) {
        players[player]->addGuess(dialog.getMulti(), score, "");
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
