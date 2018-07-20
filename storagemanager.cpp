#include "storagemanager.h"

QString StorageManager::rootPath = "";
const QString StorageManager::storageFilesSuffix = ".dat";
const QString StorageManager::storageDirName = "data";

//Logical System
const QString StorageManager::logicalSystemsDirName = "Logical Systems";
const QString StorageManager::logicalSystemsRecordsFileName = "Logical Systems Records";
const QString StorageManager::logicalSystemDataFileName = "logicalsystem";

//Theory
const QString StorageManager::theoriesDirName = "Theories";
const QString StorageManager::theoriesRecordsFileName = "Theories Records";
const QString StorageManager::theoryDataFileName = "theory";

QString StorageManager::logicalSystemsRecordsPath()
{
    return logicalSystemsDirPath() +  "/" + logicalSystemsRecordsFileName + storageFilesSuffix;
}

const QString StorageManager::theoriesDirPath(const QString &logicalSystemName)
{
    return logicalSystemsDirPath() + "/" + logicalSystemName + "/" + theoriesDirName;
}

const QString StorageManager::theoriesRecordsPath(const QString &logicalSystemName)
{
    return theoriesDirPath(logicalSystemName) + "/" + theoriesRecordsFileName + storageFilesSuffix;
}

QDir StorageManager::accessTheoriesDir(const QString &logicalSystemName)
{
    QDir theoriesDir(theoriesDirPath(logicalSystemName));
    if(!theoriesDir.exists())
    {
        QString errorMsg;
        errorMsg += "Failed to load theories directory at:";
        errorMsg += QString("\"") + theoriesDirPath(logicalSystemName) + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }

    return theoriesDir;
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
    QFile logicalSystemsRecordsFile(logicalSystemsRecordsPath());
    if(!logicalSystemsRecordsFile.open(QIODevice::ReadOnly))
    {
        QString errorMsg;
        errorMsg += "Failed to load logical systems records file at:";
        errorMsg += QString("\"") + logicalSystemsRecordsPath() + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }
    QDataStream in(&logicalSystemsRecordsFile);

    QVector<LogicalSystemRecord> logicalSystemsRecords;
    in >> logicalSystemsRecords;

    return logicalSystemsRecords;
}

void StorageManager::storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records)
{
    QFile logicalSystemsRecordsFile(logicalSystemsRecordsPath());
    if(!logicalSystemsRecordsFile.open(QIODevice::WriteOnly))
    {
        QString errorMsg;
        errorMsg += "Failed to load logical systems records file at:";
        errorMsg += QString("\"") + logicalSystemsRecordsPath() + "\"";

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

    const QString newLogicalSystemDataPath = logicalSystemsDirPath() + "/" + system.getName() + "/" + logicalSystemDataFileName + storageFilesSuffix;

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

QVector<TheoryRecord> StorageManager::retrieveTheoriesRecords(const QString &logicalSystemName)
{
    QFile theoriesRecordsFile(theoriesRecordsPath(logicalSystemName));
    if(!theoriesRecordsFile.open(QIODevice::ReadOnly))
    {
        QString errorMsg;
        errorMsg += "Failed to load theories records file at:";
        errorMsg += QString("\"") + theoriesRecordsPath(logicalSystemName) + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }
    QDataStream in(&theoriesRecordsFile);

    QVector<TheoryRecord> theoriesRecords;
    in >> theoriesRecords;

    return theoriesRecords;
}

StorageManager::storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records)
{
    QFile theoriesRecordsFile(theoriesRecordsPath(logicalSystemName));
    if(!theoriesRecordsFile.open(QIODevice::WriteOnly))
    {
        QString errorMsg;
        errorMsg += "Failed to load theories records file at:";
        errorMsg += QString("\"") + theoriesRecordsPath(logicalSystemName) + "\"";

        throw std::logic_error(errorMsg.toStdString());
    }
    QDataStream out(&theoriesRecordsFile);

    out << records;
}

void StorageManager::createTheoryDir(const QString &logicalSystemName, const Theory &theory)
{
    QDir theoriesDir = accessTheoriesDir(logicalSystemName);

    if(!theoriesDir.mkdir(theory.getName()))
    {
        throw std::runtime_error("Couldn't create theory directory!");
    }

    const QString newTheoryDataPath = theoriesDirPath(logicalSystemName) + "/" + theory.getName() + "/" + theoryDataFileName + storageFilesSuffix;

    QFile newtheoryDataFile(newTheoryDataPath);
    if(!newtheoryDataFile.open(QIODevice::WriteOnly))
    {
        throw std::runtime_error("Couldn't create theory data file!");
    }
    QDataStream out(&newtheoryDataFile);
    out << theory; //This is a key point! FIXME!
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

