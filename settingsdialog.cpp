#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "configuration.h"

SettingsDialog::SettingsDialog(const Configuration &settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->durationEdit->setText(QString::number(settings.getDuration()));
    ui->imageHeightEdit->setText(QString::number(settings.getImageHeight()));
    ui->imageWidthEdit->setText(QString::number(settings.getImageWidth()));
    for (int size : settings.getSizes()) {
        ui->pixelSizesList->addItem(QString::number(size));
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::getDuration() const
{
    return ui->durationEdit->text().toInt();
}

int SettingsDialog::getMaxHeight() const
{
    return ui->imageHeightEdit->text().toInt();
}

int SettingsDialog::getMaxWidth() const
{
    return ui->imageWidthEdit->text().toInt();
}
