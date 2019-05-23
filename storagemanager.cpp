#include "storagemanager.h"
#include "logicalsystem.h"
#include "logicalsystemrecord.h"
#include "theoryrecord.h"
#include "proofrecord.h"
#include "theory.h"
#include "pluginmanager.h"
#include "theorypluginsrecord.h"

QString StorageManager::rootPath = "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox";
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

//Proof
const QString StorageManager::proofsDirName = "Proofs";
const QString StorageManager::proofsRecordsFileName = "proofsrecords";
const QString StorageManager::proofsIdFileName = "idfile";

//Plugins
const QString StorageManager::pluginDataFileName = "plugins";
const QString StorageManager::pluginsDirName = "plugins";
const QString StorageManager::inferenceRulesPluginsDirName = "Inference Rules";
const QString StorageManager::signaturePluginsDirName = "Signatures";
const QString StorageManager::inferenceTacticsPluginsDirName = "Inference Tactics";
const QString StorageManager::preProcessorPluginsDirName = "Pre Processors";
const QString StorageManager::postProcessorPluginsDirName = "Post Processors";

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

QString StorageManager::logicalSystemPluginsDataFilePath(const QString &logicalSystemName)
{
    return logicalSystemDirPath(logicalSystemName) + "/" + pluginsDirName + storageFilesSuffix;
}

QString StorageManager::theoriesDirPath(const QString &logicalSystemName)
{
    return logicalSystemDirPath(logicalSystemName) + "/" + theoriesDirName;
}

QString StorageManager::theoriesRecordsPath(const QString &logicalSystemName)
{
    return theoriesDirPath(logicalSystemName) + "/" + theoriesRecordsFileName + storageFilesSuffix;
}

QString StorageManager::theoryDirPath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoriesDirPath(logicalSystemName) + "/" + theoryName;
}

QString StorageManager::theoryDataFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoryDirPath(logicalSystemName, theoryName) + "/" + theoryDataFileName + storageFilesSuffix;
}

QString StorageManager::theoryPluginsDataFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoryDirPath(logicalSystemName, theoryName) + "/" + pluginDataFileName + storageFilesSuffix;
}

QString StorageManager::getProofIdFileName()
{
    return proofsIdFileName;
}

QString StorageManager::proofsDirPath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoryDirPath(logicalSystemName, theoryName) + "/" + proofsDirName;
}

QString StorageManager::proofsRecordsFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return proofsDirPath(logicalSystemName, theoryName) + "/" + proofsRecordsFileName + storageFilesSuffix;
}

QString StorageManager::proofsIdFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return proofsDirPath(logicalSystemName, theoryName) + "/" + proofsIdFileName + storageFilesSuffix;
}

QString StorageManager::proofDataFilePath(const QString &logicalSystemName, const QString &theoryName, const unsigned int id)
{
    return proofsDirPath(logicalSystemName, theoryName) + "/" + QString::number(id) + storageFilesSuffix;
}

QString StorageManager::pluginsDirPath()
{
    return rootPath + "/" + pluginsDirName;
}

QString StorageManager::inferenceRulesPluginsDirPath()
{
    return pluginsDirPath() + "/" + inferenceRulesPluginsDirName;
}

QString StorageManager::signaturesPluginsDirPath()
{
    return pluginsDirPath() + "/" + signaturePluginsDirName;
}

QString StorageManager::inferenceTacticsPluginsDirPath()
{
    return pluginsDirPath() + "/" + inferenceTacticsPluginsDirName;
}

QString StorageManager::preProcessorsPluginsDirPath()
{
    return pluginsDirPath() + "/" + preProcessorPluginsDirName;
}

QString StorageManager::postProcessorsPluginsDirPath()
{
    return pluginsDirPath() + "/" + postProcessorPluginsDirName;
}

QString StorageManager::inferenceRulePluginPath(const QString &pluginName)
{
    return inferenceRulesPluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::signaturePluginPath(const QString &pluginName)
{
    return signaturesPluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::inferenceTacticPluginPath(const QString &pluginName)
{
    return inferenceTacticsPluginsDirPath() + "/" + pluginName  + ".dll";
}

QString StorageManager::preProcessorPluginPath(const QString &pluginName)
{
    return preProcessorsPluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::postProcessorPluginPath(const QString &pluginName)
{
    return postProcessorsPluginsDirPath() + "/" + pluginName + ".dll";
}

QStringList StorageManager::convertPluginNamesToPaths(const QStringList &pluginNamesList, QString pluginPathFunction(const QString&))
{
    QStringList pathList;
    std::for_each(pluginNamesList.begin(), pluginNamesList.end(), [&pathList, pluginPathFunction](const QString &pluginName)
    {
        pathList << pluginPathFunction(pluginName);
    });

    return pathList;
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

void StorageManager::checkDirExistence(const QDir &dir)
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
    return retrieveRecords<LogicalSystemRecord>(logicalSystemsRecordsPath());
}

void StorageManager::storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records)
{
    storeRecords<LogicalSystemRecord>(records, logicalSystemsRecordsPath());
}

QString StorageManager::logicalSystemsDirPath()
{
    return storageDirPath() + "/"  + logicalSystemsDirName;
}

void StorageManager::createLogicalSystemDir(const LogicalSystem &system, const QStringList &inferenceRulesNamesList)
{
    QDir dir(logicalSystemsDirPath());
    const QString logicalSystemName = system.getName();

    //Logical Systems Directory
    checkDirExistence(dir);
    mkDir(dir, logicalSystemName);

    //New Logical System Directory
    dir.cd(logicalSystemName);
    mkDir(dir, "Theories");

    //Serialization
    writeComponent(logicalSystemPluginsDataFilePath(logicalSystemName), inferenceRulesNamesList);
    writeComponent(logicalSystemDataFilePath(logicalSystemName), system);

    //Theories Directory
    dir.cd("Theories");
    QFile theoriesRecordsFile(theoriesRecordsPath(logicalSystemName));
    accessFile(theoriesRecordsFile, QIODevice::WriteOnly);
}

void StorageManager::deleteLogicalSystemDir(const QString &systemName)
{
    QDir directory(logicalSystemDirPath(systemName));
    rmDir(directory);
}

void StorageManager::saveLogicalSystem(const LogicalSystem &system)
{
    //NOTE What is the purpose of this function?
    writeComponent<LogicalSystem>(logicalSystemDataFilePath(system.getName()), system);
}

void StorageManager::loadLogicalSystem(const QString &systemName, LogicalSystem * &loadedSystem)
{
    QStringList inferenceRulesNames;
    readComponent(logicalSystemPluginsDataFilePath(systemName), inferenceRulesNames);
    const QStringList inferenceRulesPaths = convertPluginNamesToPaths(inferenceRulesNames, inferenceRulePluginPath);
    QVector<shared_ptr<const InferenceRule>> inferenceRules = PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPaths);

    QFile dataFile(logicalSystemDataFilePath(systemName));
    accessFile(dataFile, QIODevice::ReadOnly);
    QDataStream stream(&dataFile);
    loadedSystem = new LogicalSystem(stream, inferenceRules);
}

QVector<TheoryRecord> StorageManager::retrieveTheoriesRecords(const QString &logicalSystemName)
{
    return retrieveRecords<TheoryRecord>(theoriesRecordsPath(logicalSystemName));
}

void StorageManager::storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records)
{
    storeRecords<TheoryRecord>(records, theoriesRecordsPath(logicalSystemName));
}

void StorageManager::createTheoryDir(const QString &logicalSystemName, const Theory &theory, const TheoryPluginsRecord &pluginsRecord)
{
    const QString theoryName = theory.getName();
    QDir theoriesDir(theoriesDirPath(logicalSystemName));
    mkDir(theoriesDir, theoryName);

    writeComponent(theoryPluginsDataFilePath(logicalSystemName, theory.getName()), pluginsRecord);
    writeComponent(theoryDataFilePath(logicalSystemName, theory.getName()), theory);
}

void StorageManager::deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName)
{
    QDir theoryDir(theoryDirPath(logicalSystemName, theoryName));
    rmDir(theoryDir);
}

void StorageManager::saveTheory(Theory &theory)
{
    writeComponent<Theory>(theoryDataFilePath(theory.getParentLogic()->getName(), theory.getName()), theory);
}

void StorageManager::loadTheory(const LogicalSystem &parentLogic, const QString &theoryName, Theory * &theory)
{
    //Load Theory Plugins Record
    const QString logicalSystemName = parentLogic.getName();
    TheoryPluginsRecord pluginsRecord;
    readComponent(theoryPluginsDataFilePath(logicalSystemName, theoryName), pluginsRecord);

    //Load Plugins
    const QString signaturePluginPath = StorageManager::signaturePluginPath(pluginsRecord.signaturePluginName);
    const QStringList inferenceTacticsPluginsPaths = convertPluginNamesToPaths(pluginsRecord.inferenceTacticsPluginsNameList, inferenceTacticPluginPath);
    const QStringList preProcessorsPluginsPaths = convertPluginNamesToPaths(pluginsRecord.preProcessorsPluginsNameList, preProcessorPluginPath);
    const QStringList postProcessorsPluginsPaths = convertPluginNamesToPaths(pluginsRecord.postProcessorsPluginsNameList, postProcessorPluginPath);
    shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(signaturePluginPath);
    QVector<shared_ptr<const InferenceTactic>> inferenceTactics = PluginManager::fetchPluginVector<const InferenceTactic>(inferenceTacticsPluginsPaths);
    QVector<shared_ptr<StringProcessor>> preProcessors = PluginManager::fetchPluginVector<StringProcessor>(preProcessorsPluginsPaths);
    QVector<shared_ptr<StringProcessor>> postProcessors = PluginManager::fetchPluginVector<StringProcessor>(postProcessorsPluginsPaths);

    //Load Theory
    QFile dataFile(StorageManager::theoryDataFilePath(logicalSystemName, theoryName));
    accessFile(dataFile, QIODevice::ReadOnly);
    QDataStream stream(&dataFile);
    theory = new Theory(&parentLogic,
                        signature,
                        inferenceTactics,
                        preProcessors,
                        postProcessors,
                        stream);
}

QVector<ProofRecord> StorageManager::retrieveProofsRecords(const QString &logicalSystemName, const QString &theoryName)
{
    return retrieveRecords<ProofRecord>(proofsRecordsFilePath(logicalSystemName, theoryName));
}

unsigned int StorageManager::retrieveCurrentProofId(const QString &logicalSystemName, const QString &theoryName)
{
    unsigned int id;
    readComponent(proofsIdFilePath(logicalSystemName, theoryName), id);
    return id;
}

void StorageManager::storeProofsRecords(const QString &logicalSystemName, const QString &theoryName, const QVector<ProofRecord> &records)
{
    storeRecords<ProofRecord>(records, proofsRecordsFilePath(logicalSystemName, theoryName));
}

const QString StorageManager::storageDirPath()
{
    return rootPath + "/" + storageDirName;
}

