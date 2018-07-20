#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QFile>
#include <QDir>
#include "logicalsystemrecord.h"
#include "logicalsystem.h"

class StorageManager
{
public:
    static QString getRootPath();
    static void setRootPath(const QString &value);

    static QVector<LogicalSystemRecord> retrieveLogicalSystemsRecords();
    static void storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records);

    static QString logicalSystemsDirPath();

    static void createLogicalSystemDir(const LogicalSystem &system);
    static void deleteLogicalSystemDir(const QString &systemName);

    static void loadLogicalSystem(const QString &systemName, LogicalSystem * const system);

private:
    static const QString storageFilesSuffix;
    static const QString storageDirName;
    static const QString logicalSystemsDirName;
    static const QString logicalSystemsRecordsFileName;
    static const QString logicalSystemDataFileName;

    static QString getLogicalSystemsRecordsPath();

    static QDir accessLogicalSystemsDir();

    static QString rootPath;
};

#endif // STORAGEMANAGER_H
