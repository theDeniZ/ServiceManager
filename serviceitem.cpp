#include "serviceitem.h"

ServiceItem::ServiceItem(ServiceItemType itemType, ServiceTime itemTime) {
    this->type = itemType;
    this->time = itemTime;
}

QString ServiceItem::toString() {
    return QString("%1").arg((int)this->type) + QString(";0x%1;0;0").arg((int)this->time);
}

QString TimeStringValue(ServiceTime time) {
    return time == ok ? "OK" : time == late ? "Late" : "Over";
}

int IndexForTime(ServiceTime time) {
    switch (time) {
    case ok: return 0;
    case late: return 1;
    case over: return 2;
    }
}

QStringList ServiceTimeList() {
    return QStringList() << TimeStringValue(ok) << TimeStringValue(late) << TimeStringValue(over);
}

int IndexForService(ServiceItemType type) {
    switch (type) {
    case engineOil: return 0;
    case frontBrake: return 1;
    case brakeFluid: return 2;
    case microFilter: return 3;
    case recirculatingAirFilter: return 4;
    case rearBreak: return 5;
    case sparkPlugs: return 6;
    case airFilter: return 7;
    case fuelFilter: return 8;
    case vehicleCheck: return 9;
    case preDelivery: return 10;
    case serviceInspection: return 11;
    case statutoryInspection: return 12;
    case emissionsTest: return 13;
    }
}

ServiceItemType ServiceForIndex(int index) {
    switch (index) {
    case 0: return engineOil;
    case 1: return frontBrake;
    case 2: return brakeFluid;
    case 3: return microFilter;
    case 4: return recirculatingAirFilter;
    case 5: return rearBreak;
    case 6: return sparkPlugs;
    case 7: return airFilter;
    case 8: return fuelFilter;
    case 9: return vehicleCheck;
    case 10: return preDelivery;
    case 11: return serviceInspection;
    case 12: return statutoryInspection;
    case 13: return emissionsTest;
    default: return engineOil;
    }
}

QString ServiceStringValue(ServiceItemType item) {
    switch (item) {
    case engineOil: return "Engine oil";
    case frontBrake: return "Front brakes";
    case brakeFluid: return "Brake fluid";
    case microFilter: return "Micro-filter";
    case recirculatingAirFilter: return "Recirculating air filter";
    case rearBreak: return "Rear brakes";
    case sparkPlugs: return "Spark plugs";
    case airFilter: return "Air filter component";
    case fuelFilter: return "Fuel filter";
    case vehicleCheck: return "Vehicle check";
    case preDelivery: return "Pre delivery Check";
    case serviceInspection: return "Service inspection";
    case statutoryInspection: return "Statutory Inspection";
    case emissionsTest: return "Emissions test";
    }
}

QStringList ServiceItemsList() {
    return QStringList() << ServiceStringValue(engineOil) << ServiceStringValue(frontBrake) << ServiceStringValue(brakeFluid) << ServiceStringValue(microFilter)
                         << ServiceStringValue(recirculatingAirFilter) << ServiceStringValue(rearBreak) << ServiceStringValue(sparkPlugs) << ServiceStringValue(airFilter)
                         << ServiceStringValue(fuelFilter) << ServiceStringValue(vehicleCheck) << ServiceStringValue(preDelivery) << ServiceStringValue(serviceInspection)
                         << ServiceStringValue(statutoryInspection) << ServiceStringValue(emissionsTest);
}
