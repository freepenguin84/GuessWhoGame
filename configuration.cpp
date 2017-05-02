#include "configuration.h"
#include "settingsdialog.h"

#include <QSharedData>

class ConfigurationData : public QSharedData
{
public:
    ConfigurationData() {}
    ConfigurationData(const ConfigurationData &other) : QSharedData(other) {}
    ~ConfigurationData() {}

    int imageHeight = 0;
    int imageWidth = 0;
    int duration = 0;
    QVector<int> sizes = { 2, 4, 5, 6, 7, 8, 10, 12, 14, 17, 21, 25, 30, 36, 43, 51, 62, 74, 89, 107, 128 };
    //QVector<int> sizes = { 128, 107, 89, 74, 62, 51, 43, 36, 30, 25, 21, 17, 14, 12, 10, 8, 7, 6, 5, 4, 2 };
};

Configuration::Configuration()
{
    d = new ConfigurationData;
}

Configuration::Configuration(const Configuration &other) : d(other.d)
{

}

Configuration &Configuration::operator=(const Configuration &other)
{
    if (this == &other) return *this;
    d = other.d;
    return *this;
}

Configuration::~Configuration()
{

}

void Configuration::readSettings(QSettings &settings)
{
    settings.beginGroup("Images");
    d->imageWidth = settings.value("imageWidth", 1920).toInt();
    d->imageHeight = settings.value("imageHeight", 1080).toInt();
    d->duration = settings.value("duration", 1000).toInt();
    settings.endGroup();
}

void Configuration::writeSettings(QSettings &settings)
{
    settings.beginGroup("Images");
    settings.setValue("imageWidth", d->imageWidth);
    settings.setValue("imageHeight", d->imageHeight);
    settings.setValue("duration", d->duration);
    settings.endGroup();
}


int Configuration::getImageHeight() const
{
    return d->imageHeight;
}

void Configuration::setImageHeight(int value)
{
    d->imageHeight = value;
}

int Configuration::getImageWidth() const
{
    return d->imageWidth;
}

void Configuration::setImageWidth(int value)
{
    d->imageWidth = value;
}

int Configuration::getDuration() const
{
    return d->duration;
}

void Configuration::setDuration(int value)
{
    d->duration = value;
}

QVector<int> Configuration::getSizes() const
{
    return d->sizes;
}

void Configuration::setSizes(const QVector<int> &value)
{
    d->sizes = value;
}

void Configuration::showDialog()
{
    SettingsDialog settingsDialog(*this);
    if (settingsDialog.exec()) {
        setDuration(settingsDialog.getDuration());
        setImageHeight(settingsDialog.getMaxHeight());
        setImageWidth(settingsDialog.getMaxWidth());
    }

}
