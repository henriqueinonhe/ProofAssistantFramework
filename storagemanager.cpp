#include "storagemanager.h"

StorageManager::StorageManager(const QString &rootPath) :
    rootPath(rootPath)
{

}

QString StorageManager::getRootPath() const
{
    return rootPath;
}

const QString StorageManager::getLogicalSystemsRecordsPath() const
{
    return logicalSystemsDirPath() +  "/" + logicalSystemsRecordsFileName + storageFilesSuffix;
}

QVector<LogicalSystemRecord> StorageManager::retrieveLogicalSystemsRecords() const
{
    QFile logicalSystemsRecordsFile(getLogicalSystemsRecordsPath());
    logicalSystemsRecordsFile.open(QIODevice::ReadOnly);
    QDataStream in(&logicalSystemsRecordsFile);

    QVector<LogicalSystemRecord> logicalSystemsRecords;
    in >> logicalSystemsRecords;

    return logicalSystemsRecords;
}

void StorageManager::storeLogicalSystemRecord(const LogicalSystem &system) const
{
    QVector<LogicalSystemRecord> logicalSystemRecords = retrieveLogicalSystemsRecords();
    const LogicalSystemRecord newRecord(system.getName(), system.getDescription());

    logicalSystemRecords.push_back(newRecord);

    QFile logicalSystemsRecordsFile(getLogicalSystemsRecordsPath());
    logicalSystemsRecordsFile.open(QIODevice::WriteOnly);
    QDataStream out(&logicalSystemsRecordsFile);

    out << logicalSystemRecords;
}

QString StorageManager::logicalSystemsDirPath() const
{
    return rootPath + "/" + storageDirName + "/"  + logicalSystemsDirName;
}
