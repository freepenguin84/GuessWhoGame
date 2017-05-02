#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "configuration.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(const Configuration &settings, QWidget *parent = 0);
    ~SettingsDialog();
    int getDuration() const;
    int getMaxHeight() const;
    int getMaxWidth() const;
private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
