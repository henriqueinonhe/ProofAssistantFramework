#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QFile>
#include <QDir>
#include "logicalsystemrecord.h"
#include "logicalsystem.h"
#include "theoryrecord.h"

class StorageManager
{
public:
    static QString getRootPath();
    static void setRootPath(const QString &value);

    //Logical System
    static QVector<LogicalSystemRecord> retrieveLogicalSystemsRecords();
    static void storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records);

    static void createLogicalSystemDir(const LogicalSystem &system);
    static void deleteLogicalSystemDir(const QString &systemName);

    static void loadLogicalSystem(const QString &systemName, LogicalSystem * const system);

    //Theory
    static QVector<TheoryRecord> retrieveTheoriesRecords(const QString &logicalSystemName);
    static storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records);

    static void createTheoryDir(const QString &logicalSystemName, const Theory &theory);
    static void deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName);

    static void loadTheory(const QString &logicalSystemName, const QString &theoryName, Theory * const theory);

private:
    static const QString storageFilesSuffix;
    static const QString storageDirName;

    //Logical System
    static const QString logicalSystemsDirName;
    static const QString logicalSystemsRecordsFileName;
    static const QString logicalSystemDataFileName;
    static QString logicalSystemsDirPath();
    static QString logicalSystemsRecordsPath();

    //Theory
    static const QString theoriesDirName;
    static const QString theoriesRecordsFileName;
    static const QString theoryDataFileName;
    static const QString theoriesDirPath(const QString &logicalSystemName);
    static const QString theoriesRecordsPath(const QString &logicalSystemName);

    static QDir accessLogicalSystemsDir();

    static QString rootPath;
};

#endif // STORAGEMANAGER_H
