#ifndef GUESSDIALOG_H
#define GUESSDIALOG_H

#include <QDialog>

namespace Ui {
class GuessDialog;
}

class GuessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GuessDialog(int score, QWidget *parent = 0);
    ~GuessDialog();
    int getMulti() const;

public slots:
    void on_x1Button_clicked();
    void on_x2Button_clicked();
    void on_x3Button_clicked();
private:
    Ui::GuessDialog *ui;
    int multi;
};

#endif // GUESSDIALOG_H
