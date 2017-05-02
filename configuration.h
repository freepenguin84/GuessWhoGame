#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QVector>
#include <QSettings>
#include <QSharedDataPointer>

class ConfigurationData;
class Configuration {
public:
    Configuration();
    Configuration(const Configuration &other);
    Configuration& operator=(const Configuration &other);
    ~Configuration();

    void readSettings(QSettings &settings);
    void writeSettings(QSettings &settings);

    int getImageHeight() const;
    void setImageHeight(int value);

    int getImageWidth() const;
    void setImageWidth(int value);

    int getDuration() const;
    void setDuration(int value);

    QVector<int> getSizes() const;
    void setSizes(const QVector<int> &value);

    void showDialog();
private:
    QSharedDataPointer<ConfigurationData> d;
};

#endif // CONFIGURATION_H
