#include "guesswho.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuessWho w;
    w.show();

    return a.exec();
}
