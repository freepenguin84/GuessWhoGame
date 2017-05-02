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
}

PlayersPage::~PlayersPage()
{
    delete ui;
}

void PlayersPage::initializePage()
{
    addPlayerRow();
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
    playerEdit->setFocus();
}

void PlayersPage::on_addPlayerButton_clicked()
{
    addPlayerRow();
}
