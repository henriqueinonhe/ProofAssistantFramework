#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <QFile>
#include <QDir>
#include <QDataStream>

class LogicalSystem;
class Theory;
class TheoryRecord;
class LogicalSystemRecord;
class ProofRecord;
class TheoryPluginsRecord;
class InferenceRule;
class InferenceTactic;
class Signature;
class StringProcessor;
class Proof;
class LogicalSystemPluginsRecord;

//TODO Split class in two, one for paths and dirs and other for storing/retrieving

namespace std
{
    template <class T> class shared_ptr;
}

class StorageManager
{
public:
    static QString getRootPath();
    static void setRootPath(const QString &value);

    //Logical System
    static QVector<LogicalSystemRecord> retrieveLogicalSystemsRecords();
    static QStringList logicalSystemsNamesList();
    static bool logicalSystemExists(const QString &systemName);
    static void storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records);
    static void storeLogicalSystemData(const QString &systemName, const LogicalSystem &system);
    static void createTheoriesRecordsFile(const QString &systemName);
    static void setupLogicalSystemDir(const LogicalSystem &system, const LogicalSystemPluginsRecord &pluginsRecord);
    static void deleteLogicalSystemDir(const QString &systemName);
    static LogicalSystem loadLogicalSystem(const QString &systemName);
    static LogicalSystemPluginsRecord retrieveLogicalSystemPluginsRecord(const QString &systemName);
    static void storeLogicalSystemPluginsRecord(const QString &systemName, const LogicalSystemPluginsRecord &pluginsRecord);
    static QVector<std::shared_ptr<const InferenceRule>> loadInferenceRules(const QString &systemName);

    //Theory
    static QVector<TheoryRecord> retrieveTheoriesRecords(const QString &logicalSystemName);
    static QStringList theoriesNamesList(const QString &logicalSystemName);
    static bool theoryExists(const QString &logicalSystemName, const QString &theoryName);
    static void storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records);
    static void storeTheoryData(const QString &logicalSystemName, const Theory &theory);
    static void setupTheoryDir(const QString &logicalSystemName, const Theory &theory, const TheoryPluginsRecord &pluginsRecord);
    static void deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName);
    static Theory loadTheory(const LogicalSystem &parentLogic, const QString &theoryName);
    static void storeTheoryPluginsRecord(const QString &logicalSystemName, const QString &theoryName, const TheoryPluginsRecord &pluginsRecord);
    static TheoryPluginsRecord retrieveTheoryPluginsRecord(const QString &logicalSystemName, const QString &theoryName);
    static void storeTheoryPluginsData(const QString &logicalSystemName, const QString &theoryName, const Theory &theory);
    static void loadTheoryPlugins(const QString &logicalSystemName,
                                  const QString &theoryName,
                                  std::shared_ptr<Signature> &signature,
                                  QVector<std::shared_ptr<const InferenceTactic>> &inferenceTactics,
                                  QVector<std::shared_ptr<StringProcessor>> &preProcessors,
                                  QVector<std::shared_ptr<StringProcessor>> &postProcessors);

    //Proof
    static QVector<ProofRecord> retrieveProofsRecords(const QString &logicalSystemName, const QString &theoryName);
    static QStringList proofsNamesList(const QString &logicalSystemName, const QString &theoryName);
    static bool proofExists(const QString &logicalSystemName, const QString &theoryName, const QString &proofName);
    static unsigned int retrieveCurrentProofId(const QString &logicalSystemName, const QString &theoryName);
    static void storeCurrentProofId(const QString &logicalSystemName, const QString &theoryName, const unsigned int id);
    static void storeProofsRecords(const QString &logicalSystemName, const QString &theoryName, const QVector<ProofRecord> &records);
    static void storeProofData(const QString &logicalSystemName, const QString &theoryName, const Proof &proof);

    //Plugins
    static QStringList signaturePluginsList();
    static bool signaturePluginExists(const QString &pluginName);
    static QStringList inferenceRulesPluginsList();
    static bool inferenceRulePluginExists(const QString &pluginName);
    static QStringList inferenceTacticsPluginsList();
    static bool inferenceTacticPluginExists(const QString &pluginName);
    static QStringList preProcessorPluginsList();
    static bool preProcessorPluginExists(const QString &pluginName);
    static QStringList postProcessorPluginsList();
    static bool postProcessorPluginExists(const QString &pluginName);
    static QStringList proofPluginsList();
    static bool proofPluginExists(const QString &pluginName);
    static QStringList proofPrinterPluginsList();
    static bool proofPrinterPluginExists(const QString &pluginName);

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
    static QString logicalSystemPluginsRecordFilePath(const QString &logicalSystemName);

    //Theory
    static const QString theoriesDirName;
    static const QString theoriesRecordsFileName;
    static const QString theoryDataFileName;
    static QString theoriesDirPath(const QString &logicalSystemName);
    static QString theoriesRecordsPath(const QString &logicalSystemName);
    static QString theoryDirPath(const QString &logicalSystemName, const QString &theoryName);
    static QString theoryDataFilePath(const QString &logicalSystemName, const QString &theoryName);
    static QString theoryPluginsRecordFilePath(const QString &logicalSystemName, const QString &theoryName);
    static QString theoryPluginsDataFilePath(const QString &logicalSystemName, const QString &theoryName);

    //Proof
    static const QString proofsDirName;
    static const QString proofsRecordsFileName;
    static const QString proofsIdFileName;
    static QString proofsDirPath(const QString &logicalSystemName, const QString &theoryName);
    static QString proofsRecordsFilePath(const QString &logicalSystemName, const QString &theoryName);
    static QString proofsIdFilePath(const QString &logicalSystemName, const QString &theoryName);
    static QString proofDataFilePath(const QString &logicalSystemName, const QString &theoryName, const unsigned int id);

    //Plugins
    static const QString pluginsDirName;
    static const QString pluginsDataFileName;
    static const QString pluginsRecordFileName;
    static const QString inferenceRulesPluginsDirName;
    static const QString signaturePluginsDirName;
    static const QString inferenceTacticsPluginsDirName;
    static const QString preProcessorPluginsDirName;
    static const QString postProcessorPluginsDirName;
    static const QString proofPluginsDirName;
    static const QString proofPrinterPluginsDirName;
    static QString pluginsDirPath();
    static QString signaturePluginsDirPath();
    static QString inferenceRulePluginsDirPath();
    static QString inferenceTacticPluginsDirPath();
    static QString preProcessorPluginsDirPath();
    static QString postProcessorPluginsDirPath();
    static QString proofPluginsDirPath();
    static QString proofPrinterPluginsDirPath();
    static QString signaturePluginPath(const QString &pluginName);
    static QString inferenceRulePluginPath(const QString &pluginName);
    static QString inferenceTacticPluginPath(const QString &pluginName);
    static QString preProcessorPluginPath(const QString &pluginName);
    static QString postProcessorPluginPath(const QString &pluginName);
    static QString proofPluginPath(const QString &pluginName);
    static QString proofPrinterPluginPath(const QString &pluginName);
    static QStringList convertPluginNamesToPaths(const QStringList &pluginNamesList, QString pluginPathFunction(const QString &));

private:

    //Templates
    template<class T>
    static QVector<T> retrieveRecords(const QString &recordsFilePath)
    {
        QVector<T> records;
        readComponent<QVector<T>>(recordsFilePath, records);

        return records;
    }

    template<class T>
    static void storeRecords(const QVector<T> &records, const QString &recordsFilePath)
    {
        writeComponent<QVector<T>>(recordsFilePath, records);
    }

    template <class T>
    static QStringList namesListFromRecords(const QString &recordsFilePath)
    {
        const QVector<T> records = retrieveRecords<T>(recordsFilePath);
        QStringList namesList;
        for(const T &record : records)
        {
            namesList << record.getName();
        }

        return namesList;
    }

    template<class T>
    static void writeComponent(const QString &dataFilePath, const T &component)
    {
        QFile dataFile(dataFilePath);
        accessFile(dataFile, QIODevice::WriteOnly);
        QDataStream stream(&dataFile);
        stream << component;
    }

    template<class T>
    static void appendComponent(const QString &dataFilePath, const T &component)
    {
        QFile dataFile(dataFilePath);
        accessFile(dataFile, QIODevice::Append);
        QDataStream stream(&dataFile);
        stream << component;
    }

    template<class T>
    static void readComponent(const QString &dataFilePath, T &component)
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
    static QStringList listDirPlugins(const QString &dirPath);

    static QString rootPath;
};

#endif // STORAGEMANAGER_H
