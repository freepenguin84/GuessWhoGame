#ifndef IMAGESPAGE_H
#define IMAGESPAGE_H

#include <QWizardPage>

namespace Ui {
class ImagesPage;
}

class ImagesPage : public QWizardPage
{
    Q_OBJECT
    Q_PROPERTY(QStringList filenames READ filenames WRITE setFilenames NOTIFY filenamesChanged)
public:
    explicit ImagesPage(QWidget *parent = 0);
    ~ImagesPage();
    virtual bool isComplete() const override;
    QStringList filenames();
public slots:
    void setFilenames(QStringList list);
signals:
    void filenamesChanged();
protected:

private:
    Ui::ImagesPage *ui;
    void addFilename(QString filename);
private slots:
    void on_addFilesButton_clicked();
    void on_removeButton_clicked();
};

#endif // IMAGESPAGE_H
