#ifndef CLEMENTINEDBUSCONTROLLER_H
#define CLEMENTINEDBUSCONTROLLER_H
#include <QtDBus>
#include <QObject>

class ClementineDbusController :public QObject
{
    Q_OBJECT
public:
    ClementineDbusController();
    ~ClementineDbusController();
    void setVolumeStep(double stp);
    QDBusMessage IncreaseVolume();
    QDBusMessage DecreaseVolume();
    QDBusMessage NextTrack();
    QDBusMessage PrevTrack();
private:
    double volume;
    double step;
    QDBusMessage setClementineVolume();
    void getClementineVolume();
};

#endif // CLEMENTINEDBUSCONTROLLER_H
