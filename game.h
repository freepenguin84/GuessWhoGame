#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>
#include <QPixmap>
#include <QTimer>
#include <QSettings>
#include "configuration.h"

class Player;

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(const Configuration &configuration, QObject *parent = 0);
    void setFileNames(QStringList value);
    void addPlayer(QString name);
    QPixmap getScaledImage(const int index) const;
    void start();
    void nextImage();
    void refreshImage();
    void startSlideshow();
    void stopSlideshow();
    void revealImage();
    QList<Player *> getPlayers() const;

public slots:
    void showWizard();
    void showGuessDialog(int player);
signals:
    void imageChanged(const QPixmap& pixmap);
    void wizardCompleted();
private:
    int currentImageIndex = 0;
    int pixelCountDown = 20;
    QTimer timer;
    QPixmap currentImage;
    QStringList fileNames;
    QList<Player*> players;
    const Configuration &config;
};

#endif // GAME_H
