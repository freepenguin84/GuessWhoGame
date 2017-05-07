#include "playerinfo.h"
#include "ui_playerinfo.h"
#include "player.h"

PlayerInfo::PlayerInfo(Player *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerInfo)
{
    ui->setupUi(this);
    this->player = player;
}

PlayerInfo::~PlayerInfo()
{
    delete ui;
}

void PlayerInfo::setPlayer(Player *player)
{
    update();
}

void PlayerInfo::update()
{
    ui->nameLabel->setText(player->getName());
    ui->scoreLabel->setText(QString::number(player->getScore()));
}
