#ifndef PLAYERSPAGE_H
#define PLAYERSPAGE_H

#include <QWizardPage>

namespace Ui {
class PlayersPage;
}

class PlayersPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit PlayersPage(QWidget *parent = 0);
    ~PlayersPage();

    void initializePage();
    int getPlayerCount() const;

private:
    Ui::PlayersPage *ui;
    int playerCount = 0;
    void addPlayerRow();
private slots:
    void on_addPlayerButton_clicked();
};

#endif // PLAYERSPAGE_H
