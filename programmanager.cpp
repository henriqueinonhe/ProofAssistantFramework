#include "programmanager.h"
#include "logicalsystemrecord.h"
#include "theoryrecord.h"
#include "storagemanager.h"
#include "theorybuilder.h"
#include "pluginmanager.h"
#include "proofrecord.h"
#include "proof.h"
#include "proofassistant.h"
#include "logicalsystempluginsrecord.h"

ProgramManager::ProgramManager() :
    activeLogicalSystem(nullptr),
    activeTheory(nullptr)
{

}

LogicalSystem *ProgramManager::getActiveLogicalSystem() const
{
    if(activeLogicalSystem.get() == nullptr)
    {
        throw std::runtime_error("There is currently no active logical system!");
    }
    return activeLogicalSystem.get();
}

bool ProgramManager::checkLogicalSystemNameCollision(const QString &name) const
{
    const auto records = StorageManager::retrieveLogicalSystemsRecords();
    return std::any_of(records.begin(), records.end(), [&name](const LogicalSystemRecord &record)
    {
        return record.getName() == name;
    });
}

void ProgramManager::loadTheory(const QString &name)
{
    checkActiveLogicalSystem();
    Theory *theory = nullptr;
    StorageManager::loadTheory(*activeLogicalSystem, name, theory);
    activeTheory.reset(theory);
}

void ProgramManager::unloadTheory()
{
    activeTheory = nullptr;
}

Theory *ProgramManager::getActiveTheory() const
{
    checkActiveTheory();
    return activeTheory.get();
}

void ProgramManager::addPreProcessorPlugin(const QString &processorPluginName) const
{
    checkActiveTheory();
    const auto processor = PluginManager::fetchPlugin<StringProcessor>(StorageManager::preProcessorPluginPath(processorPluginName));

    auto &theory = *activeTheory;
    theory.getPreFormatter().addProcessor(processor);

    const auto logicalSystemName = activeLogicalSystem->getName();
    const auto theoryName = activeTheory->getName();
    auto pluginsRecord = StorageManager::retrieveTheoryPluginsRecord(logicalSystemName, theoryName);
    pluginsRecord.preProcessorsPluginsNameList << processorPluginName;
    StorageManager::storeTheoryPluginsRecord(logicalSystemName, theoryName, pluginsRecord);
}

void ProgramManager::addPostProcessorPlugin(const QString &processorPluginName) const
{
    checkActiveTheory();
    const auto processor = PluginManager::fetchPlugin<StringProcessor>(StorageManager::postProcessorPluginPath(processorPluginName));

    auto &theory = *activeTheory;
    theory.getPostFormatter().addProcessor(processor);

    const auto logicalSystemName = activeLogicalSystem->getName();
    const auto theoryName = activeTheory->getName();
    auto pluginsRecord = StorageManager::retrieveTheoryPluginsRecord(logicalSystemName, theoryName);
    pluginsRecord.postProcessorsPluginsNameList << processorPluginName;
    StorageManager::storeTheoryPluginsRecord(logicalSystemName, theoryName, pluginsRecord);
}

void ProgramManager::createProof(const QString &name, const QString &description, const QStringList &premises, const QString &conclusion) const
{
    checkActiveTheory();

    //Make Formulas
    const auto parser = activeTheory->parser.get();
    const auto premisesFormulas = makePremisesFormulas(premises, parser);
    auto conclusionFormula = parser->parse(conclusion);

    //Proof Id
    const auto activeLogicalSystemName = activeLogicalSystem->getName();
    const auto activeTheoryName = activeTheory->getName();
    const auto currentProofId = StorageManager::retrieveCurrentProofId(activeLogicalSystemName, activeTheoryName);

    //Proof Links
    auto proofsRecords = StorageManager::retrieveProofsRecords(activeLogicalSystemName, activeTheoryName);
    auto premisesLinks = linkPremises(currentProofId, premisesFormulas, proofsRecords);
    auto conclusionLinks = linkConclusion(currentProofId, conclusionFormula, proofsRecords);

    //Create Proof Record
    ProofRecord record(currentProofId, name, description, premisesLinks, conclusionLinks);
    proofsRecords.push_back(record);

    //Create Proof
    Proof proof(currentProofId, name, description, premisesFormulas, conclusionFormula);

    //Store
    const auto proofDataFilePath = StorageManager::proofDataFilePath(activeLogicalSystemName, activeTheoryName, currentProofId);
    const auto newProofId = currentProofId + 1;
    StorageManager::storeProofsRecords(activeLogicalSystemName, activeTheoryName, proofsRecords);
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, proof);
    StorageManager::storeCurrentProofId(activeLogicalSystemName, activeTheoryName, newProofId);
}

ProofAssistant ProgramManager::loadProof(const unsigned int proofId) const
{
    //FIXME Load Proof plugin
    checkActiveTheory();

    QFile file(StorageManager::proofDataFilePath(activeLogicalSystem->getName(), activeTheory->getName(), proofId));
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    return ProofAssistant(activeTheory.get(), Proof(stream, activeTheory->getSignature()));
}

void ProgramManager::saveProof(const ProofAssistant &assistant) const
{
    const auto proof = assistant.getProof();
    const auto activeLogicalSystemName = activeLogicalSystem->getName();
    const auto activeTheoryName = activeTheory->getName();
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, proof);
}

void ProgramManager::createTheory(const TheoryBuilder &builder, const TheoryPluginsRecord &pluginsRecord) const
{
    checkActiveLogicalSystem();

    const auto theoryName = builder.getName();
    const auto theoryDescription = builder.getDescription();

    //Theory Name Collision
    const auto activeLogicalSystemName = activeLogicalSystem->getName();
    if(checkTheoryNameCollision(activeLogicalSystemName, theoryName))
    {
        throw std::invalid_argument("There already exists a theory with this name!");
    }

    //Theory
    const auto theory = builder.build();

    //TheoryRecord
    TheoryRecord newTheoryRecord(theoryName, theoryDescription);
    auto records = StorageManager::retrieveTheoriesRecords(activeLogicalSystemName);
    records.append(newTheoryRecord);

    //File Management
    StorageManager::storeTheoriesRecords(activeLogicalSystemName, records);
    StorageManager::setupTheoryDir(activeLogicalSystemName, theory, pluginsRecord);
}

void ProgramManager::removeTheory(const QString &theoryName) const
{
    checkActiveLogicalSystem();
    const auto logicalSystemName = activeLogicalSystem->getName();
    if(!checkTheoryNameCollision(logicalSystemName, theoryName))
    {
        QString errorMsg;
        errorMsg += "There is no theory named: \"";
        errorMsg += theoryName + "\".";

        throw std::invalid_argument(errorMsg.toStdString());
    }

    const auto newRecords = getTheoryRecordsWithoutRemovedRecord(logicalSystemName, theoryName);
    StorageManager::storeTheoriesRecords(logicalSystemName, newRecords);

    StorageManager::deleteTheoryDir(logicalSystemName,theoryName);
}

bool ProgramManager::checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const
{
    const auto records = StorageManager::retrieveTheoriesRecords(logicalSystemName);
    return std::any_of(records.begin(), records.end(), [&name](const TheoryRecord &record)
    {
        return record.name == name;
    });
}

void ProgramManager::checkActiveLogicalSystem() const
{
    if(activeLogicalSystem == nullptr)
    {
        throw std::invalid_argument("There is currently no active logical system!");
    }
}

void ProgramManager::checkActiveTheory() const
{
    if(activeTheory == nullptr)
    {
        throw std::invalid_argument("There is currently no active theory!");
    }
}

QVector<shared_ptr<const InferenceRule>> ProgramManager::loadInferenceRules(const QStringList &inferenceRulesNames) const
{
    QVector<shared_ptr<const InferenceRule>> inferenceRules;
    auto inferenceRulesPathList = StorageManager::convertPluginNamesToPaths(inferenceRulesNames, StorageManager::inferenceRulePluginPath);
    return PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPathList);
}

shared_ptr<Signature> ProgramManager::loadSignature(const QString &signatureName) const
{
    auto signaturePath = StorageManager::signaturePluginPath(signatureName);
    return PluginManager::fetchPlugin<Signature>(signaturePath);
}

shared_ptr<Proof> ProgramManager::loadProofPlugin(const QString &proofName) const
{
    //NOTE Refactor
    if(proofName == "")
    {
        return make_shared<Proof>();
    }
    auto proofPath = StorageManager::proofPluginPath(proofName);
    return PluginManager::fetchPlugin<Proof>(proofPath);
}

QVector<Formula> ProgramManager::makePremisesFormulas(const QStringList &premises, const Parser *parser) const
{
    QVector<Formula> premisesFormulas;
    for(const auto &formula : premises)
    {
        premisesFormulas.push_back(parser->parse(formula));
    }
    return premisesFormulas;
}

QVector<ProofLinks> ProgramManager::linkPremises(const unsigned int currentProofId, const QVector<Formula> &premises, QVector<ProofRecord> &proofsRecords) const
{
    QVector<ProofLinks> premisesLinks;
    for(const auto &premiss : premises)
    {
        QVector<unsigned int> linkedProofsIds;
        for(auto &record : proofsRecords)
        {
            if(premiss.formattedString() == record.getConclusion())
            {
                linkedProofsIds.push_back(record.getId());
                record.addConclusionLinkId(currentProofId);
            }
        }
        premisesLinks.push_back(ProofLinks(premiss, linkedProofsIds));
    }
    return premisesLinks;
}

ProofLinks ProgramManager::linkConclusion(const unsigned int currentProofId, const Formula &conclusion, QVector<ProofRecord> &proofsRecords) const
{
    QVector<unsigned int> linkedProofsIds;
    for(ProofRecord &record : proofsRecords)
    {
        for(const auto &premiss : record.getPremises())
        {
            if(conclusion.formattedString() == premiss)
            {
                linkedProofsIds.push_back(record.getId());
                record.addPremissLinkId(conclusion, currentProofId);
                break;
            }
        }
    }
    return ProofLinks(conclusion, linkedProofsIds);
}

void ProgramManager::createLogicalSystem(const QString &name,
                                         const QString &description,
                                         const QStringList &inferenceRulesNamesList,
                                         const QString &signatureName,
                                         const QString &proofName,
                                         const Type &wffType) const
{
    if(checkLogicalSystemNameCollision(name))
    {
        throw std::invalid_argument("There already exists a logical system with this name!");
    }

    //Logical System
    const auto inferenceRules = loadInferenceRules(inferenceRulesNamesList);
    const auto signature = loadSignature(signatureName);
    const auto proof = loadProofPlugin(proofName);
    LogicalSystem logicalSystem(name, description, inferenceRules, wffType); //If Logical System creation is unsuccesfull for whatever reason (like problems loading plugins) it will throw an exception and the directories and records creation won't be carried out

    //LogicalSystemRecord
    LogicalSystemRecord newSystemRecord(name, description);
    auto records = StorageManager::retrieveLogicalSystemsRecords();
    records.append(newSystemRecord);

    //File management
    LogicalSystemPluginsRecord pluginsRecord(inferenceRulesNamesList, signatureName, proofName);
    StorageManager::storeLogicalSystemsRecords(records);
    StorageManager::setupLogicalSystemDir(logicalSystem, pluginsRecord);
}

QVector<LogicalSystemRecord> ProgramManager::getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const
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

QVector<TheoryRecord> ProgramManager::getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const
{
    const auto oldRecords = StorageManager::retrieveTheoriesRecords(logicalSystemName);
    QVector<TheoryRecord> newRecords;
    for(const auto &record : oldRecords)
    {
        if(record.name != theoryName)
        {
            newRecords.append(record);
        }
    }

    return newRecords;
}

void ProgramManager::removeLogicalSystem(const QString &name) const
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

void ProgramManager::loadLogicalSystem(const QString &name)
{
    LogicalSystem *system = nullptr;
    StorageManager::loadLogicalSystem(name, system);
    activeLogicalSystem.reset(system);
}

void ProgramManager::unloadLogicalSystem()
{
    activeLogicalSystem = nullptr;
}


