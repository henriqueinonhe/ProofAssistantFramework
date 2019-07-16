#include "storagemanager.h"
#include "logicalsystem.h"
#include "logicalsystemrecord.h"
#include "theoryrecord.h"
#include "proofrecord.h"
#include "theory.h"
#include "pluginmanager.h"
#include "theorypluginsrecord.h"
#include "proof.h"
#include "logicalsystempluginsrecord.h"

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
const QString StorageManager::proofPluginsDirName = "Proofs";

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

QString StorageManager::inferenceRulePluginsDirPath()
{
    return pluginsDirPath() + "/" + inferenceRulesPluginsDirName;
}

QStringList StorageManager::inferenceRulesPluginsList()
{
    return listDirPlugins(inferenceRulePluginsDirPath());
}

bool StorageManager::inferenceRulePluginExists(const QString &pluginName)
{
    return inferenceRulesPluginsList().contains(pluginName + ".dll");
}

QString StorageManager::signaturePluginsDirPath()
{
    return pluginsDirPath() + "/" + signaturePluginsDirName;
}

QStringList StorageManager::signaturePluginsList()
{
    return listDirPlugins(signaturePluginsDirPath());
}

bool StorageManager::signaturePluginExists(const QString &pluginName)
{
    return signaturePluginsList().contains(pluginName + ".dll");
}

QString StorageManager::inferenceTacticPluginsDirPath()
{
    return pluginsDirPath() + "/" + inferenceTacticsPluginsDirName;
}

QStringList StorageManager::inferenceTacticsPluginsList()
{
    return listDirPlugins(inferenceTacticPluginsDirPath());
}

bool StorageManager::inferenceTacticPluginExists(const QString &pluginName)
{
    return inferenceTacticsPluginsList().contains(pluginName + ".dll");
}

QString StorageManager::preProcessorPluginsDirPath()
{
    return pluginsDirPath() + "/" + preProcessorPluginsDirName;
}

QStringList StorageManager::preProcessorPluginsList()
{
    return listDirPlugins(preProcessorPluginsDirPath());
}

bool StorageManager::preProcessorPluginExists(const QString &pluginName)
{
    return preProcessorPluginsList().contains(pluginName + ".dll");
}

QString StorageManager::postProcessorPluginsDirPath()
{
    return pluginsDirPath() + "/" + postProcessorPluginsDirName;
}

QString StorageManager::proofPluginsDirPath()
{
    return pluginsDirPath() + "/" + proofPluginsDirName;
}

QStringList StorageManager::postProcessorPluginsList()
{
    return listDirPlugins(postProcessorPluginsDirPath());
}

bool StorageManager::postProcessorPluginExists(const QString &pluginName)
{
    return postProcessorPluginsList().contains(pluginName + ".dll");
}

QStringList StorageManager::proofPluginsList()
{
    return listDirPlugins(proofPluginsDirPath());
}

bool StorageManager::prooPluginExists(const QString &pluginName)
{
    return proofPluginsList().contains(pluginName + ".dll");
}

QString StorageManager::inferenceRulePluginPath(const QString &pluginName)
{
    return inferenceRulePluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::signaturePluginPath(const QString &pluginName)
{
    return signaturePluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::inferenceTacticPluginPath(const QString &pluginName)
{
    return inferenceTacticPluginsDirPath() + "/" + pluginName  + ".dll";
}

QString StorageManager::preProcessorPluginPath(const QString &pluginName)
{
    return preProcessorPluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::postProcessorPluginPath(const QString &pluginName)
{
    return postProcessorPluginsDirPath() + "/" + pluginName + ".dll";
}

QString StorageManager::proofPluginPath(const QString &pluginName)
{
    return proofPluginsDirPath() + "/" + pluginName + ".dll";
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

QStringList StorageManager::listDirPlugins(const QString &dirPath)
{
    QDir dir(dirPath);
    dir.setFilter(QDir::Files);
    dir.setNameFilters(QStringList({"*.dll"}));
    return dir.entryList();
}

void StorageManager::storeLogicalSystemPluginsData(const QString &systemName, const LogicalSystemPluginsRecord &pluginsRecord)
{
    writeComponent(logicalSystemPluginsDataFilePath(systemName), pluginsRecord);
}

void StorageManager::storeLogicalSystemData(const QString &systemName, const LogicalSystem &system)
{
    writeComponent(logicalSystemDataFilePath(systemName), system);
}

void StorageManager::createTheoriesRecordsFile(const QString &systemName)
{
    QFile theoriesRecordsFile(theoriesRecordsPath(systemName));
    accessFile(theoriesRecordsFile, QIODevice::WriteOnly);
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

QStringList StorageManager::logicalSystemsNamesList()
{
    return namesListFromRecords<LogicalSystemRecord>(logicalSystemsRecordsPath());
}

bool StorageManager::logicalSystemExists(const QString &systemName)
{
    return logicalSystemsNamesList().contains(systemName);
}

void StorageManager::storeLogicalSystemsRecords(const QVector<LogicalSystemRecord> &records)
{
    storeRecords<LogicalSystemRecord>(records, logicalSystemsRecordsPath());
}

QString StorageManager::logicalSystemsDirPath()
{
    return storageDirPath() + "/"  + logicalSystemsDirName;
}

void StorageManager::setupLogicalSystemDir(const LogicalSystem &system, const LogicalSystemPluginsRecord &pluginsRecord)
{
    QDir dir(logicalSystemsDirPath());
    const QString systemName = system.getName();

    //Make Logical System Dir
    checkDirExistence(dir);
    mkDir(dir, systemName);

    //Make Theories Dir
    dir.cd(systemName);
    mkDir(dir, "Theories");

    //Serialization
    storeLogicalSystemPluginsData(systemName, pluginsRecord);
    storeLogicalSystemData(systemName, system);

    //Theories Records
    createTheoriesRecordsFile(systemName);
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

QVector<shared_ptr<const InferenceRule>> StorageManager::loadInferenceRules(const QString &systemName)
{
    LogicalSystemPluginsRecord pluginsRecord;
    readComponent(logicalSystemPluginsDataFilePath(systemName), pluginsRecord);

    const QStringList inferenceRulesNames = pluginsRecord.getInferenceRulesNamesList();
    const QStringList inferenceRulesPaths = convertPluginNamesToPaths(inferenceRulesNames, inferenceRulePluginPath);
    return PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPaths);
}

void StorageManager::storeTheoryPluginsData(const QString &logicalSystemName, const QString &theoryName, const TheoryPluginsRecord &pluginsRecord)
{
    writeComponent(theoryPluginsDataFilePath(logicalSystemName, theoryName), pluginsRecord);
}

void StorageManager::storeTheoryData(const QString &logicalSystemName, const Theory &theory)
{
    writeComponent(theoryDataFilePath(logicalSystemName, theory.getName()), theory);
}

void StorageManager::loadTheoryPlugins(const QString &logicalSystemName, const QString &theoryName, std::shared_ptr<Signature> &signature, QVector<std::shared_ptr<const InferenceTactic> > &inferenceTactics, QVector<std::shared_ptr<StringProcessor> > &preProcessors, QVector<std::shared_ptr<StringProcessor> > &postProcessors)
{
    LogicalSystemPluginsRecord systemPluginsRecord;
    TheoryPluginsRecord theoryPluginsRecord;
    readComponent(logicalSystemPluginsDataFilePath(logicalSystemName), systemPluginsRecord);
    readComponent(theoryPluginsDataFilePath(logicalSystemName, theoryName), theoryPluginsRecord);

    const QString signaturePluginPath = StorageManager::signaturePluginPath(systemPluginsRecord.getSignatureName());
    const QStringList inferenceTacticsPluginsPaths = convertPluginNamesToPaths(theoryPluginsRecord.inferenceTacticsPluginsNameList, inferenceTacticPluginPath);
    const QStringList preProcessorsPluginsPaths = convertPluginNamesToPaths(theoryPluginsRecord.preProcessorsPluginsNameList, preProcessorPluginPath);
    const QStringList postProcessorsPluginsPaths = convertPluginNamesToPaths(theoryPluginsRecord.postProcessorsPluginsNameList, postProcessorPluginPath);
    signature = PluginManager::fetchPlugin<Signature>(signaturePluginPath);
    inferenceTactics = PluginManager::fetchPluginVector<const InferenceTactic>(inferenceTacticsPluginsPaths);
    preProcessors = PluginManager::fetchPluginVector<StringProcessor>(preProcessorsPluginsPaths);
    postProcessors = PluginManager::fetchPluginVector<StringProcessor>(postProcessorsPluginsPaths);
}

void StorageManager::loadLogicalSystem(const QString &systemName, LogicalSystem * &loadedSystem)
{
    QVector<shared_ptr<const InferenceRule>> inferenceRules = loadInferenceRules(systemName);

    QFile dataFile(logicalSystemDataFilePath(systemName));
    accessFile(dataFile, QIODevice::ReadOnly);
    QDataStream stream(&dataFile);
    loadedSystem = new LogicalSystem(stream, inferenceRules);
}

QVector<TheoryRecord> StorageManager::retrieveTheoriesRecords(const QString &logicalSystemName)
{
    return retrieveRecords<TheoryRecord>(theoriesRecordsPath(logicalSystemName));
}

QStringList StorageManager::theoriesNamesList(const QString &logicalSystemName)
{
    return namesListFromRecords<TheoryRecord>(theoriesRecordsPath(logicalSystemName));
}

bool StorageManager::theoryExists(const QString &logicalSystemName, const QString &theoryName)
{
    return theoriesNamesList(logicalSystemName).contains(theoryName);
}

void StorageManager::storeTheoriesRecords(const QString &logicalSystemName, const QVector<TheoryRecord> &records)
{
    storeRecords<TheoryRecord>(records, theoriesRecordsPath(logicalSystemName));
}

void StorageManager::setupTheoryDir(const QString &logicalSystemName, const Theory &theory, const TheoryPluginsRecord &pluginsRecord)
{
    const QString theoryName = theory.getName();
    QDir theoriesDir(theoriesDirPath(logicalSystemName));
    mkDir(theoriesDir, theoryName);
    theoriesDir.cd(theoryName);
    theoriesDir.mkdir("Proofs");

    const unsigned int initialProofId = 0;
    storeCurrentProofId(logicalSystemName, theoryName, initialProofId);
    storeProofsRecords(logicalSystemName, theoryName, QVector<ProofRecord>());
    storeTheoryPluginsData(logicalSystemName, theory.getName(), pluginsRecord);
    storeTheoryData(logicalSystemName, theory);
}

void StorageManager::deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName)
{
    QDir theoryDir(theoryDirPath(logicalSystemName, theoryName));
    rmDir(theoryDir);
}

void StorageManager::saveTheory(Theory &theory)
{
    //FIXME What is this for?
    writeComponent<Theory>(theoryDataFilePath(theory.getParentLogic()->getName(), theory.getName()), theory);
}

void StorageManager::loadTheory(const LogicalSystem &parentLogic, const QString &theoryName, Theory * &theory)
{
    //Load Theory Plugins
    const QString logicalSystemName = parentLogic.getName();

    shared_ptr<Signature> signature;
    QVector<shared_ptr<const InferenceTactic>> inferenceTactics;
    QVector<shared_ptr<StringProcessor>> preProcessors;
    QVector<shared_ptr<StringProcessor>> postProcessors;
    loadTheoryPlugins(logicalSystemName, theoryName, signature, inferenceTactics, preProcessors, postProcessors);

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

QStringList StorageManager::proofsNamesList(const QString &logicalSystemName, const QString &theoryName)
{
    return namesListFromRecords<ProofRecord>(proofsRecordsFilePath(logicalSystemName, theoryName));
}

bool StorageManager::proofExists(const QString &logicalSystemName, const QString &theoryName, const QString &proofName)
{
    return proofsNamesList(logicalSystemName, theoryName).contains(proofName);
}

unsigned int StorageManager::retrieveCurrentProofId(const QString &logicalSystemName, const QString &theoryName)
{
    unsigned int id;
    readComponent(proofsIdFilePath(logicalSystemName, theoryName), id);
    return id;
}

void StorageManager::storeCurrentProofId(const QString &logicalSystemName, const QString &theoryName, const unsigned int id)
{
    writeComponent(StorageManager::proofsIdFilePath(logicalSystemName, theoryName), id);
}

void StorageManager::storeProofsRecords(const QString &logicalSystemName, const QString &theoryName, const QVector<ProofRecord> &records)
{
    storeRecords<ProofRecord>(records, proofsRecordsFilePath(logicalSystemName, theoryName));
}

void StorageManager::storeProofData(const QString &logicalSystemName, const QString &theoryName, const Proof &proof)
{
    writeComponent(StorageManager::proofDataFilePath(logicalSystemName, theoryName, proof.getId()), proof);
}

const QString StorageManager::storageDirPath()
{
    return rootPath + "/" + storageDirName;
}

