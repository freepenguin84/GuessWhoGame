#ifndef GUESSWHO_H
#define GUESSWHO_H

#include <QMainWindow>
#include "configuration.h"

class Game;
class PlayerInfo;
class QPushButton;
class QLabel;

namespace Ui {
class GuessWho;
}

class GuessWho : public QMainWindow
{
    Q_OBJECT

public:
    explicit GuessWho(QWidget *parent = 0);
    ~GuessWho();
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
    QLabel* pixelCountLabel;
signals:
    void guessed(int player);
private slots:
    void togglePlayerButtons(bool enabled);
    void refreshImage(const QPixmap& image);
    void updateInfo(const int playerIndex);
    void showPlayerButtons();
    void on_actionNewGame_triggered();
    void on_actionSettings_triggered();
    void on_showScoreButton_toggled();
    void on_actionToggleControls_toggled(bool checked);
    void on_toggleShowButton_toggled();
    void on_nextButton_clicked();
    void on_revealButton_clicked();
};

#endif // GUESSWHO_H
