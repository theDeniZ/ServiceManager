#ifndef SERVICEMANAGER_H
#define SERVICEMANAGER_H

#include <QObject>
#include <servicehistory.h>

class ServiceManager {
public:
    bool eraseHistory = true;

    ServiceManager();
    ServiceHistory * readHistoryFromFile(QString);
    bool writeHistoryToFile(QString, ServiceHistory *);
};

#endif // SERVICEMANAGER_H
