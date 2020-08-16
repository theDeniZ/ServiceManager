#include "servicemanager.h"
#include <QTextStream>
#include <QDebug>
#include <QFile>

ServiceManager::ServiceManager() {}

ServiceHistory * ServiceManager::readHistoryFromFile(QString fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return nullptr;
    }
    QTextStream in(&file);
    QString fileContent = in.readAll();
    file.close();
    this->eraseHistory = fileContent.contains("steuern_servicehistory_erase");
    return new ServiceHistory(fileContent);
}

bool ServiceManager::writeHistoryToFile(QString fileName, ServiceHistory * history) {
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
        return false;
    }
    QTextStream out(&file);
    int startingOffset = 0;
    if (this->eraseHistory) {
        out << "1|g_mmi|steuern_servicehistory_erase\r\n";
        startingOffset = 1;
    }
    out << history->toString(startingOffset);
    file.flush();
    file.close();
    return true;
}
