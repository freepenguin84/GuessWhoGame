#ifndef GUESSWHO_H
#define GUESSWHO_H

#include <QMainWindow>
#include "configuration.h"

class Game;
class PlayerInfo;
class QPushButton;

namespace Ui {
class GuessWho;
}

class GuessWho : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuessWho(QWidget *parent = 0);
    ~GuessWho();

public slots:
    void refreshImage(const QPixmap& image);
    void updateInfo(const int playerIndex);
    void showPlayerButtons();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::GuessWho *ui;
    Game *game = nullptr;
    Configuration config;
    QList<PlayerInfo*> infos;
    QList<QPushButton*> buttons;
    void readSettings();
    void writeSettings();
    void connectUI();
signals:
    void guessed(int player);
private slots:
    void togglePlayerButtons(bool enabled);
    void on_actionNewGame_triggered();
    void on_actionFullscreen_triggered();
    void on_actionSettings_triggered();
    void on_showScoreButton_toggled();
};

#endif // GUESSWHO_H
