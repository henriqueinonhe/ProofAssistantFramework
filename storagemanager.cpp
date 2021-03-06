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
#include "proofprinter.h"

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
const QString StorageManager::pluginsDirName = "plugins";
const QString StorageManager::pluginsDataFileName = "pluginsdata";
const QString StorageManager::pluginsRecordFileName = "pluginsrecord";
const QString StorageManager::inferenceRulesPluginsDirName = "Inference Rules";
const QString StorageManager::signaturePluginsDirName = "Signatures";
const QString StorageManager::inferenceTacticsPluginsDirName = "Inference Tactics";
const QString StorageManager::preProcessorPluginsDirName = "Pre Processors";
const QString StorageManager::postProcessorPluginsDirName = "Post Processors";
const QString StorageManager::proofPluginsDirName = "Proofs";
const QString StorageManager::proofPrinterPluginsDirName = "Proof Printers";

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

QString StorageManager::logicalSystemPluginsRecordFilePath(const QString &logicalSystemName)
{
    return logicalSystemDirPath(logicalSystemName) + "/" + pluginsRecordFileName + storageFilesSuffix;
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

QString StorageManager::theoryPluginsRecordFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoryDirPath(logicalSystemName, theoryName) + "/" + pluginsRecordFileName + storageFilesSuffix;
}

QString StorageManager::theoryPluginsDataFilePath(const QString &logicalSystemName, const QString &theoryName)
{
    return theoryDirPath(logicalSystemName, theoryName) + "/" + pluginsDataFileName + storageFilesSuffix;
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

QString StorageManager::proofPrinterPluginsDirPath()
{
    return pluginsDirPath() + "/" + proofPrinterPluginsDirName;
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

bool StorageManager::proofPluginExists(const QString &pluginName)
{
    return proofPluginsList().contains(pluginName + ".dll");
}

QStringList StorageManager::proofPrinterPluginsList()
{
    return listDirPlugins(proofPrinterPluginsDirPath());
}

bool StorageManager::proofPrinterPluginExists(const QString &pluginName)
{
    return proofPrinterPluginsList().contains(pluginName + ".dll");
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

QString StorageManager::proofPrinterPluginPath(const QString &pluginName)
{
    return proofPrinterPluginsDirPath() + "/" + pluginName + ".dll";
}

QStringList StorageManager::convertPluginNamesToPaths(const QStringList &pluginNamesList, QString pluginPathFunction(const QString&))
{
    QStringList pathList;
    for(const auto &pluginName : pluginNamesList)
    {
        pathList << pluginPathFunction(pluginName);
    }

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
    const auto systemName = system.getName();

    //Make Logical System Dir
    checkDirExistence(dir);
    mkDir(dir, systemName);

    //Make Theories Dir
    dir.cd(systemName);
    mkDir(dir, "Theories");

    //Serialization
    storeLogicalSystemPluginsRecord(systemName, pluginsRecord);
    storeLogicalSystemData(systemName, system);

    //Theories Records
    createTheoriesRecordsFile(systemName);
}

void StorageManager::deleteLogicalSystemDir(const QString &systemName)
{
    QDir directory(logicalSystemDirPath(systemName));
    rmDir(directory);
}

QVector<shared_ptr<const InferenceRule>> StorageManager::loadInferenceRules(const QString &systemName)
{
    LogicalSystemPluginsRecord pluginsRecord;
    readComponent(logicalSystemPluginsRecordFilePath(systemName), pluginsRecord); //NOTE Refactor

    const auto inferenceRulesNames = pluginsRecord.getInferenceRulesNamesList();
    const auto inferenceRulesPaths = convertPluginNamesToPaths(inferenceRulesNames, inferenceRulePluginPath);
    return PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPaths);
}

void StorageManager::storeTheoryData(const QString &logicalSystemName, const Theory &theory)
{
    writeComponent(theoryDataFilePath(logicalSystemName, theory.getName()), theory);
}

void StorageManager::loadTheoryPlugins(const QString &logicalSystemName, const QString &theoryName, std::shared_ptr<Signature> &signature, QVector<std::shared_ptr<const InferenceTactic> > &inferenceTactics, QVector<std::shared_ptr<StringProcessor> > &preProcessors, QVector<std::shared_ptr<StringProcessor> > &postProcessors, std::shared_ptr<ProofPrinter> &proofPrinter)
{
    //NOTE Maybe refactor using tuples
    LogicalSystemPluginsRecord systemPluginsRecord;
    TheoryPluginsRecord theoryPluginsRecord;
    readComponent(logicalSystemPluginsRecordFilePath(logicalSystemName), systemPluginsRecord);
    readComponent(theoryPluginsRecordFilePath(logicalSystemName, theoryName), theoryPluginsRecord);

    const auto signaturePluginPath = StorageManager::signaturePluginPath(systemPluginsRecord.getSignaturePluginName());
    const auto inferenceTacticsPluginsPaths = convertPluginNamesToPaths(theoryPluginsRecord.inferenceTacticsPluginsNameList, inferenceTacticPluginPath);
    const auto preProcessorsPluginsPaths = convertPluginNamesToPaths(theoryPluginsRecord.preProcessorsPluginsNameList, preProcessorPluginPath);
    const auto postProcessorsPluginsPaths = convertPluginNamesToPaths(theoryPluginsRecord.postProcessorsPluginsNameList, postProcessorPluginPath);
    const auto proofPrinterPluginPath = StorageManager::proofPrinterPluginPath(theoryPluginsRecord.proofPrinterPluginName);

    const auto pluginsDataFilePath = theoryPluginsDataFilePath(logicalSystemName, theoryName);
    QFile dataFile(pluginsDataFilePath);
    dataFile.open(QIODevice::ReadOnly);
    QDataStream stream(&dataFile);

    signature = PluginManager::fetchPlugin<Signature>(stream, signaturePluginPath); //Must be fetched first in order to be used by StringProcessors
    inferenceTactics = PluginManager::fetchPluginVector<const InferenceTactic>(inferenceTacticsPluginsPaths);
    preProcessors = PluginManager::fetchPluginVector(stream, preProcessorsPluginsPaths, signature.get());
    postProcessors = PluginManager::fetchPluginVector(stream, postProcessorsPluginsPaths, signature.get());
    proofPrinter = PluginManager::fetchPlugin<ProofPrinter>(stream, proofPrinterPluginPath);
}


LogicalSystem StorageManager::loadLogicalSystem(const QString &systemName)
{
    const auto inferenceRules = loadInferenceRules(systemName);

    QFile dataFile(logicalSystemDataFilePath(systemName));
    accessFile(dataFile, QIODevice::ReadOnly);
    QDataStream stream(&dataFile);
    return LogicalSystem(stream, inferenceRules);
}

LogicalSystemPluginsRecord StorageManager::retrieveLogicalSystemPluginsRecord(const QString &systemName)
{
    LogicalSystemPluginsRecord pluginsRecord;
    readComponent(logicalSystemPluginsRecordFilePath(systemName), pluginsRecord);
    return pluginsRecord;
}

void StorageManager::storeLogicalSystemPluginsRecord(const QString &systemName, const LogicalSystemPluginsRecord &pluginsRecord)
{
    writeComponent(logicalSystemPluginsRecordFilePath(systemName), pluginsRecord);
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

void StorageManager::setupTheoryDir(const QString &logicalSystemName, const Theory &theory, const TheoryPluginsRecord &pluginsRecord, const ProofPrinter &proofPrinter)
{
    const auto theoryName = theory.getName();
    QDir theoriesDir(theoriesDirPath(logicalSystemName));
    mkDir(theoriesDir, theoryName);
    theoriesDir.cd(theoryName);
    theoriesDir.mkdir("Proofs");

    const auto initialProofId = 0;
    storeCurrentProofId(logicalSystemName, theoryName, initialProofId);
    storeProofsRecords(logicalSystemName, theoryName, QVector<ProofRecord>());
    storeTheoryPluginsRecord(logicalSystemName, theory.getName(), pluginsRecord);
    storeTheoryPluginsData(logicalSystemName, theory.getName(), theory, proofPrinter);
    storeTheoryData(logicalSystemName, theory);
}

void StorageManager::deleteTheoryDir(const QString &logicalSystemName, const QString &theoryName)
{
    QDir theoryDir(theoryDirPath(logicalSystemName, theoryName));
    rmDir(theoryDir);
}

Theory StorageManager::loadTheory(const LogicalSystem &parentLogic, const QString &theoryName, std::shared_ptr<ProofPrinter> &proofPrinter)
{
    //Load Theory Plugins
    const auto logicalSystemName = parentLogic.getName();

    shared_ptr<Signature> signature;
    QVector<shared_ptr<const InferenceTactic>> inferenceTactics;
    QVector<shared_ptr<StringProcessor>> preProcessors;
    QVector<shared_ptr<StringProcessor>> postProcessors;
    loadTheoryPlugins(logicalSystemName, theoryName, signature, inferenceTactics, preProcessors, postProcessors, proofPrinter);

    //Load Theory
    QFile dataFile(StorageManager::theoryDataFilePath(logicalSystemName, theoryName));
    accessFile(dataFile, QIODevice::ReadOnly);
    QDataStream stream(&dataFile);
    return Theory(&parentLogic,
           signature,
           inferenceTactics,
           preProcessors,
           postProcessors,
           stream);
}

TheoryPluginsRecord StorageManager::retrieveTheoryPluginsRecord(const QString &logicalSystemName, const QString &theoryName)
{
    TheoryPluginsRecord pluginsRecord;
    readComponent(theoryPluginsRecordFilePath(logicalSystemName, theoryName), pluginsRecord);
    return pluginsRecord;
}

void StorageManager::storeTheoryPluginsRecord(const QString &logicalSystemName, const QString &theoryName, const TheoryPluginsRecord &pluginsRecord)
{
    writeComponent(theoryPluginsRecordFilePath(logicalSystemName, theoryName), pluginsRecord);
}

void StorageManager::storeTheoryPluginsData(const QString &logicalSystemName, const QString &theoryName, const Theory &theory, const ProofPrinter &proofPrinter)
{
    const auto dataFilePath = theoryPluginsDataFilePath(logicalSystemName, theoryName);
    writeComponent(dataFilePath, *theory.getSignature()); //TODO Refactor Using reference
    appendComponent(dataFilePath, theory.getPreFormatter().getProcessors());
    appendComponent(dataFilePath, theory.getPostFormatter().getProcessors());
    appendComponent(dataFilePath, proofPrinter);
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

