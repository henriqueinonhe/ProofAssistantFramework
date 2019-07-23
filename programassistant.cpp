#include "programassistant.h"
#include "storagemanager.h"
#include "logicalsystemrecord.h"
#include "pluginmanager.h"
#include "logicalsystem.h"
#include "logicalsystempluginsrecord.h"

ProgramAssistant::ProgramAssistant()
{

}


bool ProgramAssistant::checkLogicalSystemNameCollision(const QString &name) const
{
    const auto records = StorageManager::retrieveLogicalSystemsRecords();
    return std::any_of(records.begin(), records.end(), [&name](const LogicalSystemRecord &record)
    {
        return record.getName() == name;
    });
}

QVector<shared_ptr<const InferenceRule>> ProgramAssistant::loadInferenceRulesPlugins(const QStringList &inferenceRulesNames) const
{
    QVector<shared_ptr<const InferenceRule>> inferenceRules;
    auto inferenceRulesPathList = StorageManager::convertPluginNamesToPaths(inferenceRulesNames, StorageManager::inferenceRulePluginPath);
    return PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPathList);
}

shared_ptr<Signature> ProgramAssistant::validateSignaturePlugin(const QString &signatureName) const
{
    auto signaturePath = StorageManager::signaturePluginPath(signatureName);
    return PluginManager::fetchPlugin<Signature>(signaturePath);
}

void ProgramAssistant::validateProofPlugin(const QString &proofPluginName) const
{
    if(proofPluginName == "") //Refactor using a constant
    {
        return;
    }
    else
    {
        auto proofPluginPath = StorageManager::proofPluginPath(proofPluginName);
        PluginManager::fetchPlugin<Proof>(proofPluginPath);
    }
}

void ProgramAssistant::validateProofPrinterPlugin(const QString &proofPrinterPluginName) const
{
    auto proofPrinterPluginPath = StorageManager::proofPrinterPluginPath(proofPrinterPluginName);
    PluginManager::fetchPlugin<ProofPrinter>(proofPrinterPluginPath);
}

void ProgramAssistant::createLogicalSystem(const QString &name,
                                           const QString &description,
                                           const QStringList &inferenceRulesNamesList,
                                           const QString &signaturePluginName,
                                           const QString &proofPluginName,
                                           const QString &proofPrinterPluginName,
                                           const Type &wffType) const
{
    if(checkLogicalSystemNameCollision(name))
    {
        throw std::invalid_argument("There already exists a logical system with this name!");
    }

    //Logical System
    /* If Logical System creation is unsuccesfull for
     * whatever reason (like problems loading plugins)
     * it will throw an exception and the directories
     * and records creation won't be carried out */
    const auto inferenceRules = loadInferenceRulesPlugins(inferenceRulesNamesList);
    validateSignaturePlugin(signaturePluginName);
    validateProofPlugin(proofPluginName);
    LogicalSystem logicalSystem(name, description, inferenceRules, wffType);

    //LogicalSystemRecord
    LogicalSystemRecord newSystemRecord(name, description);
    auto records = StorageManager::retrieveLogicalSystemsRecords();
    records.append(newSystemRecord);

    //File management
    LogicalSystemPluginsRecord pluginsRecord(inferenceRulesNamesList, signaturePluginName, proofPluginName, proofPrinterPluginName);
    StorageManager::storeLogicalSystemsRecords(records);
    StorageManager::setupLogicalSystemDir(logicalSystem, pluginsRecord);
}

QVector<LogicalSystemRecord> ProgramAssistant::getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const
{
    const auto oldRecords = StorageManager::retrieveLogicalSystemsRecords();
    QVector<LogicalSystemRecord> newRecords;
    for(const auto &record : oldRecords)
    {
        if(record.getName() != name)
        {
            newRecords.append(record);
        }
    }

    return newRecords;
}

void ProgramAssistant::removeLogicalSystem(const QString &name) const
{
    //Maybe this should be made more efficient!
    if(!checkLogicalSystemNameCollision(name))
    {
        QString errorMsg;
        errorMsg += "There is no logical system named: \"";
        errorMsg += name + "\".";
    }

    const auto newRecords = getLogicalSystemRecordsWithoutRemovedRecord(name);
    StorageManager::storeLogicalSystemsRecords(newRecords);
    StorageManager::deleteLogicalSystemDir(name);
}

void ProgramAssistant::loadLogicalSystem(const QString &name)
{
    LogicalSystem *system = nullptr;
    StorageManager::loadLogicalSystem(name, system);
    //Return LogicalSystemAssistant
}



