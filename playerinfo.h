#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QWidget>

class Player;

namespace Ui {
class PlayerInfo;
}

class PlayerInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInfo(Player* player, QWidget *parent = 0);
    ~PlayerInfo();
    void setPlayer(Player* player);
public slots:
    void update();
private:
    Ui::PlayerInfo *ui;
    Player* player;
};

#endif // PLAYERINFO_H
