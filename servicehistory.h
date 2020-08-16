#ifndef SERVICEHISTORY_H
#define SERVICEHISTORY_H

#include <QObject>
#include <QList>
#include <service.h>
#include <QString>

class ServiceHistory {
public:
    QList<Service> services;
    ServiceHistory();
    ServiceHistory(QString);
    QString toString(int);
};

#endif // SERVICEHISTORY_H
