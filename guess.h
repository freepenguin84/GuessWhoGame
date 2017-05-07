#ifndef GUESS_H
#define GUESS_H

#include <QString>

class Guess {
public:
    Guess(int personsGuessed, int score, QString fileName);
    int getScore();
private:
    int personsGuessed;
    int score;
    QString fileName;
};

#endif // GUESS_H
