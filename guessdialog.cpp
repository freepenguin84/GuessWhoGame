#include "guessdialog.h"
#include "ui_guessdialog.h"

GuessDialog::GuessDialog(int score, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuessDialog)
{
    ui->setupUi(this);
    ui->scoreLabel->setText(QString::number(score));
}

GuessDialog::~GuessDialog()
{
    delete ui;
}

void GuessDialog::on_x1Button_clicked()
{
    multi = 1;
    accept();
}

void GuessDialog::on_x2Button_clicked()
{
    multi = 2;
    accept();
}

void GuessDialog::on_x3Button_clicked()
{
    multi = 3;
    accept();
}

int GuessDialog::getMulti() const
{
    return multi;
}
