#include "storagemanager.h"

const QString StorageManager::storageFilesSuffix = ".dat";
const QString StorageManager::storageDirName = "data";
const QString StorageManager::logicalSystemsDirName = "Logical Systems";
const QString StorageManager::logicalSystemsRecordsFileName = "Logical Systems Records";
const QString StorageManager::logicalSystemDataFileName = "logicalsystem";
QString StorageManager::rootPath = "";

QString StorageManager::getLogicalSystemsRecordsPath()
{
    return logicalSystemsDirPath() +  "/" + logicalSystemsRecordsFileName + storageFilesSuffix;
}

QString StorageManager::getRootPath()
{
    return rootPath;
}

void StorageManager::setRootPath(const QString &value)
{
    rootPath = value;
}

QVector<LogicalSystemRecord> StorageManager::retrieveLogicalSystemsRecords()
{
    QFile logicalSystemsRecordsFile(getLogicalSystemsRecordsPath());
    if(!logicalSystemsRecordsFile.open(QIODevice::ReadOnly))
    {
        QString errorMsg;
        errorMsg += "Failed to load logical systems records file at:";
        errorMsg += QString("\"") + getLogicalSystemsRecordsPath() + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }
    QDataStream in(&logicalSystemsRecordsFile);

    QVector<LogicalSystemRecord> logicalSystemsRecords;
    in >> logicalSystemsRecords;

    return logicalSystemsRecords;
}

void StorageManager::storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records)
{
    QFile logicalSystemsRecordsFile(getLogicalSystemsRecordsPath());
    if(!logicalSystemsRecordsFile.open(QIODevice::WriteOnly))
    {
        QString errorMsg;
        errorMsg += "Failed to load logical systems records file at:";
        errorMsg += QString("\"") + getLogicalSystemsRecordsPath() + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }
    QDataStream out(&logicalSystemsRecordsFile);

    out << records;
}

QString StorageManager::logicalSystemsDirPath()
{
    return rootPath + "/" + storageDirName + "/"  + logicalSystemsDirName;
}

QDir StorageManager::accessLogicalSystemsDir()
{
    QDir logicalSystemsDir(logicalSystemsDirPath());
    if(!logicalSystemsDir.exists())
    {
        QString errorMsg;
        errorMsg += "Failed to load logical systems directory at:";
        errorMsg += QString("\"") + logicalSystemsDirPath() + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }

    return logicalSystemsDir;
}

void StorageManager::createLogicalSystemDir(const LogicalSystem &system)
{
    QDir logicalSystemsDir = accessLogicalSystemsDir();

    if(!logicalSystemsDir.mkdir(system.getName()))
    {
        throw std::runtime_error("Couldn't create logical system directory!");
    }

    const QString newLogicalSystemDataPath = logicalSystemsDirPath() + "/" + system.getName() + "/" + "logicalsystem" + storageFilesSuffix;

    QFile newLogicalSystemDataFile(newLogicalSystemDataPath);
    if(!newLogicalSystemDataFile.open(QIODevice::WriteOnly))
    {
        throw std::runtime_error("Couldn't create logical system data file!");
    }
    QDataStream out(&newLogicalSystemDataFile);
    out << system;
}

void StorageManager::deleteLogicalSystemDir(const QString &systemName)
{
    QDir directory = accessLogicalSystemsDir();
    directory.cd(systemName);

    if(!directory.removeRecursively())
    {
        throw std::runtime_error("Couldn't remove logical system directory!");
    }
}

void StorageManager::loadLogicalSystem(const QString &systemName, LogicalSystem * const system)
{
    const QString logicalSystemDataFilePath = logicalSystemsDirPath() + "/" +
                                              systemName + "/" +
                                              logicalSystemDataFileName +
                                              storageFilesSuffix;
    QFile logicalSystemDataFile(logicalSystemDataFilePath);
    if(!logicalSystemDataFile.open(QIODevice::ReadOnly))
    {
        throw std::runtime_error("Couldn't open logical system data file!");
    }
    QDataStream in(&logicalSystemDataFile);
    in >> *system;
}

