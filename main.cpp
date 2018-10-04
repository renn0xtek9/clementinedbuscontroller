#include <QCoreApplication>
#include <QtDBus>
#include <QDebug>
#include "clementinedbuscontroller.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClementineDbusController controller;
    controller.setVolumeStep(0.5);




    //controller.PrevTrack();
    controller.DecreaseVolume();




    return a.exec();
}
