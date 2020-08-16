#include "servicehistory.h"

ServiceHistory::ServiceHistory() {
    this->services = QList<Service>();
}

ServiceHistory::ServiceHistory(QString str) {
    this->services = QList<Service>();
    QStringList parameterList = str.split("\r\n");
    for (int i = 0; i < parameterList.count(); ++i) {
        QStringList lineParameters = parameterList[i].split("|");
        if (lineParameters.count() >= 5 && lineParameters[4].count() > 0) {
            this->services.append(Service(lineParameters[4]));
        }
    }
}

QString ServiceHistory::toString(int startingOffset) {
    QString returning = "";
    for (int i = 0; i < this->services.count(); ++i) {
        returning += QString("%1").arg(startingOffset + i + 1) + "|g_mmi|steuern_servicehistory_add||" + this->services[i].toString() + "\r\n";
    }
    return returning;
}
