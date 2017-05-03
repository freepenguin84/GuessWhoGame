#ifndef GUESSWHO_H
#define GUESSWHO_H

#include <QMainWindow>
#include "configuration.h"

class Game;

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
    void showPlayerButtons();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::GuessWho *ui;
    Game *game = nullptr;
    Configuration config;
    void readSettings();
    void writeSettings();

signals:
    void guessed(int player);
private slots:

    void on_actionNewGame_triggered();
    void on_actionFullscreen_triggered();
    void on_actionSettings_triggered();
};

#endif // GUESSWHO_H
