#include "clementinedbuscontroller.h"
ClementineDbusController::ClementineDbusController():QObject()
{
    volume=1.0;
    step=0.1;
    getClementineVolume();
}
ClementineDbusController::~ClementineDbusController()
{

}
void ClementineDbusController::setVolumeStep(double stp)
{
    stp=stp<0.0?0.01:stp;
    stp=stp>1.0?0.99:stp;
}
QDBusMessage ClementineDbusController::DecreaseVolume()
{
    volume=volume-step<0.0?0.0:volume-step;
    return setClementineVolume();
}
QDBusMessage ClementineDbusController::IncreaseVolume()
{
    volume=volume+step>1.0?1.0:volume+step;
    return setClementineVolume();
}
QDBusMessage ClementineDbusController::setClementineVolume()
{
    QDBusMessage message=QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.clementine","/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties","Set");
    message<<"org.mpris.MediaPlayer2.Player"<<"Volume"<<QVariant::fromValue(QDBusVariant(volume));
    return QDBusConnection::sessionBus().call(message);
}
QDBusMessage ClementineDbusController::NextTrack()
{
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusMessage message=QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.clementine","/org/mpris/MediaPlayer2","org.mpris.MediaPlayer2.Player","Next");
    return bus.call(message);
}
QDBusMessage ClementineDbusController::PrevTrack()
{
    QDBusConnection bus=QDBusConnection::sessionBus();
    QDBusMessage message=QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.clementine","/org/mpris/MediaPlayer2","org.mpris.MediaPlayer2.Player","Previous");
    return bus.call(message);
}
void ClementineDbusController::getClementineVolume()
{
    QDBusMessage message=QDBusMessage::createMethodCall("org.mpris.MediaPlayer2.clementine","/org/mpris/MediaPlayer2","org.freedesktop.DBus.Properties","Get");
    message<<"org.mpris.MediaPlayer2.Player"<<"Volume";
    QDBusReply<QVariant> reply(QDBusConnection::sessionBus().call(message));
    if (reply.isValid())
    {
        if (reply.value().canConvert(QMetaType::Double))
        {
           volume=reply.value().toDouble();
        }
        else
        {
            qDebug()<<"Can't retrieve volume from clementine";
        }
    }
    else
    {
        qDebug()<<"Reply not valid when asking for Clementine for volume";
    }
    return;
}
