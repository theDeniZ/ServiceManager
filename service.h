#ifndef SERVICE_H
#define SERVICE_H

#include <QObject>
#include <QDate>
#include <QList>
#include <serviceitem.h>

class Service {
public:
    QDate date;
    int milage;
    QString dealer;
    bool bmw;
    ServiceTime time;
    QList<ServiceItem> items;

    Service();
    Service(QString);
    QString toString();
};

#endif // SERVICE_H
