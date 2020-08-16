#include "service.h"


Service::Service() {
    this->date = QDate::currentDate();
    this->milage = 0;
    this->dealer = "";
    this->bmw = false;
    this->time = ok;
    this->items = QList<ServiceItem>();
}

Service::Service(QString str) {
    QRegExp tagExp(";");
    QStringList parameterList = str.split(tagExp);
    this->date = QDate(parameterList[2].toInt(), parameterList[0].toInt(), parameterList[1].toInt());
    this->milage = parameterList[4].toInt();
    this->bmw = parameterList[5].toInt() == 1;
    this->dealer = parameterList[6];
    this->time = parameterList[7] == "0x2" ? late : parameterList[7] == "0x3" ? over : ok;

    this->items = QList<ServiceItem>();
    int startOffset = 9;
    int count = parameterList[8].toInt();
    for(int i = 0; i < count; ++i) {
        ServiceTime time = parameterList[startOffset + 1] == "0x2" ? late : parameterList[startOffset + 1] == "0x3" ? over : ok;
        if (parameterList[startOffset] == "1") {
            this->items.append(ServiceItem(engineOil, time));
        } else if (parameterList[startOffset] == "2") {
            this->items.append(ServiceItem(frontBrake, time));
        } else if (parameterList[startOffset] == "3") {
            this->items.append(ServiceItem(brakeFluid, time));
        } else if (parameterList[startOffset] == "4") {
            this->items.append(ServiceItem(microFilter, time));
        } else if (parameterList[startOffset] == "5") {
            this->items.append(ServiceItem(recirculatingAirFilter, time));
        } else if (parameterList[startOffset] == "6") {
            this->items.append(ServiceItem(rearBreak, time));
        } else if (parameterList[startOffset] == "10") {
            this->items.append(ServiceItem(sparkPlugs, time));
        } else if (parameterList[startOffset] == "11") {
            this->items.append(ServiceItem(airFilter, time));
        } else if (parameterList[startOffset] == "12") {
            this->items.append(ServiceItem(fuelFilter, time));
        } else if (parameterList[startOffset] == "100") {
            this->items.append(ServiceItem(vehicleCheck, time));
        } else if (parameterList[startOffset] == "20") {
            this->items.append(ServiceItem(preDelivery, time));
        } else if (parameterList[startOffset] == "21") {
            this->items.append(ServiceItem(serviceInspection, time));
        } else if (parameterList[startOffset] == "32") {
            this->items.append(ServiceItem(statutoryInspection, time));
        } else if (parameterList[startOffset] == "33") {
            this->items.append(ServiceItem(emissionsTest, time));
        }
        startOffset += 4;
    }

}

QString Service::toString() {
    QString listSting = "";
    for (int i = 0; i < this->items.count(); ++i) {
        listSting += this->items[i].toString();
        if (i < this->items.count() - 1) {
            listSting += ";";
        }
    }
    return QString("%1;").arg((int)this->date.month()) + QString("%1;").arg((int)this->date.day()) + QString("%1;0;").arg((int)this->date.year()) +
            QString("%1;").arg(this->milage) + QString("%1;").arg(this->bmw ? 1 : 0) + this->dealer + ";" +
            QString("0x%1;").arg(this->time) + QString("%1;").arg(this->items.count()) + listSting;
}
