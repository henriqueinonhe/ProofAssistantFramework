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

QVector<shared_ptr<const InferenceRule>> ProgramAssistant::loadInferenceRules(const QStringList &inferenceRulesNames) const
{
    QVector<shared_ptr<const InferenceRule>> inferenceRules;
    auto inferenceRulesPathList = StorageManager::convertPluginNamesToPaths(inferenceRulesNames, StorageManager::inferenceRulePluginPath);
    return PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPathList);
}

shared_ptr<Signature> ProgramAssistant::loadSignature(const QString &signatureName) const
{
    auto signaturePath = StorageManager::signaturePluginPath(signatureName);
    return PluginManager::fetchPlugin<Signature>(signaturePath);
}

shared_ptr<Proof> ProgramAssistant::loadProofPlugin(const QString &proofPluginName,
                                                  const uint id,
                                                  const QString &name,
                                                  const QString &description,
                                                  const QVector<Formula> &premises,
                                                  const Formula &conclusion) const
{
    if(proofPluginName == "")//TODO Refactor using a constant
    {
        return Proof::createNewProof<Proof>(id,
                                            name,
                                            description,
                                            premises,
                                            conclusion);
    }
    else
    {
        auto prooPluginfPath = StorageManager::proofPluginPath(proofPluginName);
        return PluginManager::fetchPlugin(prooPluginfPath,
                                          id,
                                          name,
                                          description,
                                          premises,
                                          conclusion);
    }
}

void ProgramAssistant::testLoadProofPlugin(const QString &proofPluginName) const
{
    if(proofPluginName == "") //Refactor using a constat
    {
        return;
    }
    else
    {
        auto proofPluginPath = StorageManager::proofPluginPath(proofPluginName);
        PluginManager::fetchPlugin<Proof>(proofPluginPath);
    }
}

void ProgramAssistant::createLogicalSystem(const QString &name,
                                           const QString &description,
                                           const QStringList &inferenceRulesNamesList,
                                           const QString &signaturePluginName,
                                           const QString &proofPluginName,
                                           const Type &wffType) const
{
    if(checkLogicalSystemNameCollision(name))
    {
        throw std::invalid_argument("There already exists a logical system with this name!");
    }

    //Logical System
    const auto inferenceRules = loadInferenceRules(inferenceRulesNamesList);
    const auto signature = loadSignature(signaturePluginName);
    testLoadProofPlugin(proofPluginName);
    LogicalSystem logicalSystem(name, description, inferenceRules, wffType); //If Logical System creation is unsuccesfull for whatever reason (like problems loading plugins) it will throw an exception and the directories and records creation won't be carried out

    //LogicalSystemRecord
    LogicalSystemRecord newSystemRecord(name, description);
    auto records = StorageManager::retrieveLogicalSystemsRecords();
    records.append(newSystemRecord);

    //File management
    LogicalSystemPluginsRecord pluginsRecord(inferenceRulesNamesList, signaturePluginName, proofPluginName);
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



