#ifndef GAMEWIZARD_H
#define GAMEWIZARD_H

#include <QWizard>

namespace Ui {
class GameWizard;
}

class GameWizard : public QWizard
{
    Q_OBJECT

public:
    explicit GameWizard(QWidget *parent = 0);
    ~GameWizard();
    int playerCount();
private:
    Ui::GameWizard *ui;

};

#endif // GAMEWIZARD_H
