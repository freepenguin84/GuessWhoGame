#include "gamewizard.h"
#include "ui_gamewizard.h"

GameWizard::GameWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::GameWizard)
{
    ui->setupUi(this);
}

GameWizard::~GameWizard()
{
    delete ui;
}

int GameWizard::playerCount()
{
    return ui->playersPage->getPlayerCount();
}
