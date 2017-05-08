#include "playerspage.h"
#include "ui_playerspage.h"
#include "ui_playerrow.h"
#include <QLineEdit>
#include <QFormLayout>

PlayersPage::PlayersPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::PlayersPage)
{
    ui->setupUi(this);
    addPlayerRow();
}

PlayersPage::~PlayersPage()
{
    delete ui;
}

int PlayersPage::getPlayerCount() const
{
    return playerCount;
}

void PlayersPage::addPlayerRow()
{
    QLineEdit *playerEdit = new QLineEdit(this);
    ui->playersList->addRow(tr("&Name"), playerEdit);
    registerField(QString("player") + QString::number(playerCount++), playerEdit);
    if (playerCount == MAX_PLAYERS) {
        ui->addPlayerButton->setEnabled(false);
    }
    playerEdit->setFocus();
}

void PlayersPage::on_addPlayerButton_clicked()
{
    addPlayerRow();
}
