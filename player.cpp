#include "player.h"
#include "guess.h"

Player::Player(QString name)
{
    this->name = name;
}

QString Player::getName() const
{
    return name;
}

void Player::setName(const QString &value)
{
    name = value;
}

void Player::addGuess(int personsGuessed, int score, QString fileName)
{
    guesses.append(new Guess(personsGuessed, score, fileName));
}
