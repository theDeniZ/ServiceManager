#ifndef SERVICEITEM_H
#define SERVICEITEM_H

#include <QObject>
#include <QString>

enum ServiceItemType {
    engineOil=1,
    frontBrake=2,
    brakeFluid=3,
    microFilter=4,
    recirculatingAirFilter=5,
    rearBreak=6,
    sparkPlugs=10,
    airFilter=11,
    fuelFilter=12,
    vehicleCheck=100,
    preDelivery=20,
    serviceInspection=21,
    statutoryInspection=32,
    emissionsTest=33
};

enum ServiceTime { ok=1, late=2, over=3 };

QString TimeStringValue(ServiceTime time);
QString ServiceStringValue(ServiceItemType item);

int IndexForTime(ServiceTime time);
int IndexForService(ServiceItemType type);
ServiceItemType ServiceForIndex(int index);

QStringList ServiceItemsList();
QStringList ServiceTimeList();

class ServiceItem {
public:
    ServiceItemType type;
    ServiceTime time;

    ServiceItem(ServiceItemType, ServiceTime);
    ServiceItem(QString);
    QString toString();
};

#endif // SERVICEITEM_H
