#include "storagemanager.h"

QString StorageManager::rootPath = "";
const QString StorageManager::storageFilesSuffix = ".dat";
const QString StorageManager::storageDirName = "data";

//Logical System
const QString StorageManager::logicalSystemsDirName = "Logical Systems";
const QString StorageManager::logicalSystemsRecordsFileName = "logicalsystemsrecords";
const QString StorageManager::logicalSystemDataFileName = "logicalsystem";

//Theory
const QString StorageManager::theoriesDirName = "Theories";
const QString StorageManager::theoriesRecordsFileName = "theoriesrecords";
const QString StorageManager::theoryDataFileName = "theory";

QString StorageManager::logicalSystemsRecordsPath()
{
    return logicalSystemsDirPath() +  "/" + logicalSystemsRecordsFileName + storageFilesSuffix;
}

QString StorageManager::logicalSystemDirPath(const QString &logicalSystemName)
{
    return logicalSystemsDirPath() + "/" + logicalSystemName;
}

QString StorageManager::logicalSystemDataFilePath(const QString &logicalSystemName)
{
    return logicalSystemDirPath(logicalSystemName) + "/" + logicalSystemDataFileName + storageFilesSuffix;
}

const QString StorageManager::theoriesDirPath(const QString &logicalSystemName)
{
    return logicalSystemDirPath(logicalSystemName) + "/" + theoriesDirName;
}

const QString StorageManager::theoriesRecordsPath(const QString &logicalSystemName)
{
    return theoriesDirPath(logicalSystemName) + "/" + theoriesRecordsFileName + storageFilesSuffix;
}

const QString StorageManager::theoryDirPath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoriesDirPath(logicalSystemName) + "/" + theoryName;
}

const QString StorageManager::theoryDataFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoryDirPath(logicalSystemName, theoryName) + "/" + theoryDataFileName + storageFilesSuffix;
}

void StorageManager::accessFile(QFile &file, const QIODevice::OpenModeFlag &openMode)
{
    if(!file.open(openMode))
    {
        QString errorMsg;
        errorMsg += "Failed to open file at: ";
        errorMsg += "/" + file.fileName();

        throw std::runtime_error(errorMsg.toStdString());
    }
}

void StorageManager::accessDir(const QDir &dir)
{
    if(!dir.exists())
    {
        QString errorMsg;
        errorMsg += "Failed to open directory at: ";
        errorMsg += "/" + dir.absolutePath();

        throw std::runtime_error(errorMsg.toStdString());
    }
}

void StorageManager::mkDir(const QDir &dir, const QString &dirName)
{
    if(!dir.mkdir(dirName))
    {
        QString errorMsg;
        errorMsg += "Failed to create directory at: ";
        errorMsg += "/" + dir.absolutePath() + "/" + dirName;

        throw std::runtime_error(errorMsg.toStdString());
    }
}

void StorageManager::rmDir(QDir &dir)
{
    if(!dir.removeRecursively())
    {
        QString errorMsg;
        errorMsg +=  "Failed to remove directory at: ";
        errorMsg += "/" + dir.absolutePath();

        throw std::runtime_error(errorMsg.toStdString());
    }
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
    accessFile(logicalSystemsRecordsFile, QIODevice::ReadOnly);
    QDataStream in(&logicalSystemsRecordsFile);

    QVector<LogicalSystemRecord> logicalSystemsRecords;
    in >> logicalSystemsRecords;

    return logicalSystemsRecords;
}

void StorageManager::storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records)
{
    QFile logicalSystemsRecordsFile(logicalSystemsRecordsPath());
    accessFile(logicalSystemsRecordsFile, QIODevice::WriteOnly);
    QDataStream out(&logicalSystemsRecordsFile);

    out << records;
}

QString StorageManager::logicalSystemsDirPath()
{
    return storageDirPath() + "/"  + logicalSystemsDirName;
}

void StorageManager::createLogicalSystemDir(const LogicalSystem &system)
{
    QDir dir(logicalSystemsDirPath());
    const QString logicalSystemName = system.getName();
    //Logical Systems Directory
    accessDir(dir);
    mkDir(dir, logicalSystemName);

    //New Logical System Directory
    dir.cd(logicalSystemName);
    mkDir(dir, "Theories");

    const QString newLogicalSystemDataPath = logicalSystemDataFilePath(logicalSystemName);
    QFile newLogicalSystemDataFile(newLogicalSystemDataPath);
    accessFile(newLogicalSystemDataFile, QIODevice::WriteOnly);
    QDataStream out(&newLogicalSystemDataFile);
    out << system;

    //Theories Directory
    dir.cd("Theories");
    QFile theoriesRecordsFile(theoriesRecordsPath(logicalSystemName));
    accessFile(theoriesRecordsFile, QIODevice::WriteOnly);
}

void StorageManager::deleteLogicalSystemDir(const QString &systemName)
{
    QDir directory(logicalSystemDirPath(systemName));

    if(!directory.removeRecursively())
    {
        throw std::runtime_error("Couldn't remove logical system directory!");
    }
}

void StorageManager::loadLogicalSystem(const QString &systemName, LogicalSystem * const loadedSystem)
{
    QFile logicalSystemDataFile(logicalSystemDataFilePath(systemName));
    accessFile(logicalSystemDataFile, QIODevice::ReadOnly);
    QDataStream in(&logicalSystemDataFile);
    in >> *loadedSystem;
}

QVector<TheoryRecord> StorageManager::retrieveTheoriesRecords(const QString &logicalSystemName)
{
    QFile theoriesRecordsFile(theoriesRecordsPath(logicalSystemName));
    accessFile(theoriesRecordsFile, QIODevice::ReadOnly);
    QDataStream in(&theoriesRecordsFile);

    QVector<TheoryRecord> theoriesRecords;
    in >> theoriesRecords;

    return theoriesRecords;
}

void StorageManager::storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records)
{
    QFile theoriesRecordsFile(theoriesRecordsPath(logicalSystemName));
    accessFile(theoriesRecordsFile, QIODevice::WriteOnly);
    QDataStream out(&theoriesRecordsFile);

    out << records;
}

void StorageManager::createTheoryDir(const QString &logicalSystemName, const Theory &theory)
{
    const QString theoryName = theory.getName();
    QDir theoriesDir(theoriesDirPath(logicalSystemName));
    mkDir(theoriesDir, theoryName);

    QFile newTheoryDataFile(theoryDataFilePath(logicalSystemName, theoryName));
    accessFile(newTheoryDataFile, QIODevice::WriteOnly);
    QDataStream out(&newTheoryDataFile);
    out << theory;
}

void StorageManager::deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName)
{
    QDir theoryDir(theoryDirPath(logicalSystemName, theoryName));

    theoryDir.removeRecursively();
}

void StorageManager::loadTheory(const QString &logicalSystemName, const QString &theoryName, Theory * const theory)
{
    QFile theoryDataFile(theoryDataFilePath(logicalSystemName, theoryName));
    accessFile(theoryDataFile, QIODevice::ReadOnly);
    QDataStream stream(&theoryDataFile);

    stream >> *theory;
}

const QString StorageManager::storageDirPath()
{
    return rootPath + "/" + storageDirName;
}

