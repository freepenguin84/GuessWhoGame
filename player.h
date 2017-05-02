#ifndef PLAYER_H
#define PLAYER_H

#include <QList>

class Guess;
class Player {
public:
    Player(QString name);
private:
    QString name;
    QList<Guess*> guesses;
public:
    void addGuess(int personsGuessed, int score, QString fileName);
    QString getName() const;
    void setName(const QString &value);
};

#endif // PLAYER_H
