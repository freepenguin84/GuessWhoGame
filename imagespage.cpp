#include "imagespage.h"
#include "ui_imagespage.h"
#include <QFileDialog>
#include <QListWidget>

ImagesPage::ImagesPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::ImagesPage)
{
    ui->setupUi(this);
    registerField("imageFiles", this, "filenames");
    ui->removeButton->setEnabled(isComplete());
}

ImagesPage::~ImagesPage()
{
    delete ui;
}

void ImagesPage::on_addFilesButton_clicked()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Load images"), QDir::homePath(), (tr("Image files (*.jpg *.png)")));
    if (!fileNames.isEmpty()) {
        QStringList filesInList = filenames();
        for (QString filename : fileNames) {
            if (!filesInList.contains(filename)) {
                addFilename(filename);
            }
        }
        emit filenamesChanged();
    }
}

void ImagesPage::on_removeButton_clicked()
{
    qDeleteAll(ui->imageFilesList->selectedItems());
    emit completeChanged();
    ui->removeButton->setEnabled(isComplete());
}

bool ImagesPage::isComplete() const
{
    return ui->imageFilesList->count() > 0;
}

QStringList ImagesPage::filenames()
{
    QStringList result;
    for (int i = 0; i < ui->imageFilesList->count(); ++i) {
        result += ui->imageFilesList->item(i)->text();
    }
    return result;
}

void ImagesPage::setFilenames(QStringList list)
{
    ui->imageFilesList->addItems(list);
}

void ImagesPage::addFilename(QString filename)
{
    ui->imageFilesList->addItem(filename);
    emit completeChanged();
}
