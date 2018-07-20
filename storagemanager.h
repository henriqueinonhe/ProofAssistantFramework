#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QFile>
#include <QDir>
#include "logicalsystemrecord.h"
#include "logicalsystem.h"

class StorageManager
{
public:

    StorageManager(const QString &rootPath);

    QString getRootPath() const;

    QVector<LogicalSystemRecord> retrieveLogicalSystemsRecords() const;
    void storeLogicalSystemRecord(const LogicalSystem &system) const;

    QString logicalSystemsDirPath() const;

private:
    const QString storageFilesSuffix = ".dat";
    const QString storageDirName = "data";
    const QString logicalSystemsDirName = "Logical Systems";
    const QString logicalSystemsRecordsFileName = "Logical Systems Records";

    const QString getLogicalSystemsRecordsPath() const;

    QString rootPath;
};

#endif // STORAGEMANAGER_H
