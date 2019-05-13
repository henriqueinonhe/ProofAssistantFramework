#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QFile>
#include <QDir>
#include "logicalsystemrecord.h"
#include "logicalsystem.h"
#include "theoryrecord.h"
#include "proofrecord.h"

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
    static void saveLogicalSystem(const LogicalSystem &system);
    static void loadLogicalSystem(const QString &systemName, LogicalSystem &loadedSystem);

    //Theory
    static QVector<TheoryRecord> retrieveTheoriesRecords(const QString &logicalSystemName);
    static void storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records);
    static void createTheoryDir(const QString &logicalSystemName, const Theory &theory);
    static void deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName);
    static void saveTheory(Theory &theory);
    static void loadTheory(const QString &logicalSystemName, const QString &theoryName, Theory &theory);

    //Proof
    static QVector<ProofRecord> retrieveProofsRecords(const QString &logicalSystemName,
                                                      const QString &theoryName);
    static void storeProofsRecords(const QString &logicalSystemName,
                                   const QString &theoryName,
                                   const QVector<ProofRecord> &records);

    // Files, Dirs and Paths

    //Root
    static const QString storageFilesSuffix;
    static const QString storageDirName;
    static const QString storageDirPath();

    //Logical System
    static const QString logicalSystemsDirName;
    static const QString logicalSystemsRecordsFileName;
    static const QString logicalSystemDataFileName;
    static QString logicalSystemsDirPath();
    static QString logicalSystemsRecordsPath();
    static QString logicalSystemDirPath(const QString &logicalSystemName);
    static QString logicalSystemDataFilePath(const QString &logicalSystemName);

    //Theory
    static const QString theoriesDirName;
    static const QString theoriesRecordsFileName;
    static const QString theoryDataFileName;
    static QString theoriesDirPath(const QString &logicalSystemName);
    static QString theoriesRecordsPath(const QString &logicalSystemName);
    static QString theoryDirPath(const QString &logicalSystemName, const QString &theoryName);
    static QString theoryDataFilePath(const QString &logicalSystemName, const QString &theoryName);

    //Proof
    static const QString proofsDirName;
    static const QString proofsRecordsFileName;
    static QString proofsDirPath(const QString &logicalSystemName, const QString &theoryName);
    static QString proofsRecordsFilePath(const QString &logicalSystemName, const QString &theoryName);

    //Plugins
    static const QString pluginsDirName;
    static const QString inferenceRulesPluginsDirName;
    static const QString signaturePluginsDirName;
    static const QString inferenceTacticsPluginsDirName;
    static const QString preProcessorPluginsDirName;
    static const QString postProcessorPluginsDirName;
    static QString pluginsDirPath();
    static QString signaturesPluginsDirPath();
    static QString inferenceRulesPluginsDirPath();
    static QString inferenceTacticsPluginsDirPath();
    static QString preProcessorsPluginsDirPath();
    static QString postProcessorsPluginsDirPath();
    static QString signaturePluginPath(const QString &pluginName);
    static QString inferenceRulePluginPath(const QString &pluginName);
    static QString inferenceTacticPluginPath(const QString &pluginName);
    static QString preProcessorPluginPath(const QString &pluginName);
    static QString postProcessorPluginPath(const QString &pluginName);

private:
    //Templates

    template<class T>
    static QVector<T> retrieveRecords(const QString &recordsFilePath)
    {
        QVector<T> records;
        retrieveComponent<QVector<T>>(recordsFilePath, records);

        return records;
    }

    template<class T>
    static void storeRecords(const QVector<T> &records, const QString &recordsFilePath)
    {
        storeComponent<QVector<T>>(recordsFilePath, records);
    }

    template<class T>
    static void storeComponent(const QString &dataFilePath, const T &component)
    {
        QFile dataFile(dataFilePath);
        accessFile(dataFile, QIODevice::WriteOnly);
        QDataStream stream(&dataFile);
        stream << component;
    }

    template<class T>
    static void retrieveComponent(const QString &dataFilePath, T &component)
    {
        QFile dataFile(dataFilePath);
        accessFile(dataFile, QIODevice::ReadOnly);
        QDataStream stream(&dataFile);
        stream >> component;
    }

    //Files and Directories
    static void accessFile(QFile &file, const QIODevice::OpenModeFlag &openMode);
    static void checkDirExistence(const QDir &dir);
    static void mkDir(const QDir &dir, const QString &dirName);
    static void rmDir(QDir &dir);

    static QString rootPath;
};

#endif // STORAGEMANAGER_H
