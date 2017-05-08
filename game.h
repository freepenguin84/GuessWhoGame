#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>
#include <QPixmap>
#include <QTimer>
#include <QSettings>
#include "configuration.h"

namespace Ui {
class GameWizard;
}

class Player;
class QWizard;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(const Configuration &configuration, QObject *parent = 0);
    QPixmap getScaledImage(const int index) const;
    void start();
    QList<Player *> getPlayers() const;
public slots:
    void loadNextImage();
    void showNextPixelated();
    void startSlideshow();
    void stopSlideshow();
    void revealImage();
    void showWizard();
    void showGuessDialog(int player);
signals:
    void imageChanged(const QPixmap& pixmap);
    void wizardCompleted();
    void guessCompleted(int playerIndex);
    void uiChanged(bool enabled);
private:
    int currentImageIndex = 0;
    int pixelCountDown = 20;
    int currentScore = 0;
    QTimer timer;
    QPixmap currentImage;
    QStringList fileNames;
    QList<Player*> players;
    const Configuration &config;
    Ui::GameWizard *wizardUi;
};

#endif // GAME_H
