#include "theoryassistant.h"
#include "storagemanager.h"
#include "pluginmanager.h"
#include "theorypluginsrecord.h"
#include "proofrecord.h"
#include "proofassistant.h"
#include "parser.h"
#include "logicalsystempluginsrecord.h"

TheoryAssistant::TheoryAssistant(const LogicalSystem &activeLogicalSystem, Theory &&activeTheory, const shared_ptr<ProofPrinter> &proofPrinter) :
    activeLogicalSystem(activeLogicalSystem),
    activeTheory(std::move(activeTheory)),
    proofPrinter(proofPrinter)
{

}

const Theory &TheoryAssistant::getActiveTheory() const
{
    return activeTheory;
}

Signature *TheoryAssistant::accessSignaturePlugin()
{
    return activeTheory.getSignature();
}

void TheoryAssistant::addPreProcessorPlugin(const QString &processorPluginName)
{
    auto &theory = activeTheory;
    const auto processor = PluginManager::fetchPlugin(StorageManager::preProcessorPluginPath(processorPluginName), activeTheory.getSignature());

    theory.getPreFormatter().addProcessor(processor);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.preProcessorsPluginsNameList << processorPluginName;
    storeActiveTheoryPluginsRecord(pluginsRecord);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::addPostProcessorPlugin(const QString &processorPluginName)
{
    auto &theory = activeTheory;
    const auto processor = PluginManager::fetchPlugin(StorageManager::postProcessorPluginPath(processorPluginName), activeTheory.getSignature());

    theory.getPostFormatter().addProcessor(processor);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.postProcessorsPluginsNameList << processorPluginName;
    storeActiveTheoryPluginsRecord(pluginsRecord);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::removePreProcessorPlugin(const unsigned int processorIndex)
{
    auto &theory = activeTheory;
    theory.getPreFormatter().removeProcessor(processorIndex);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.preProcessorsPluginsNameList.pop_back();
    storeActiveTheoryPluginsRecord(pluginsRecord);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::removePostProcessorPlugin(const unsigned int processorIndex)
{
    auto &theory = activeTheory;
    theory.getPostFormatter().removeProcessor(processorIndex);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.postProcessorsPluginsNameList.pop_back();
    storeActiveTheoryPluginsRecord(pluginsRecord);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::turnOnPreProcessorPlugin(const unsigned int processorIndex)
{
    activeTheory.getPreFormatter().turnOnProcessor(processorIndex);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::turnOnPostProcessorPlugin(const unsigned int processorIndex)
{
    activeTheory.getPostFormatter().turnOnProcessor(processorIndex);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::turnOffPreProcessorPlugin(const unsigned int processorIndex)
{
    activeTheory.getPreFormatter().turnOffProcessor(processorIndex);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

void TheoryAssistant::turnOffPostProcessorPlugin(const unsigned int processorIndex)
{
    activeTheory.getPostFormatter().turnOffProcessor(processorIndex);
    StorageManager::storeTheoryData(activeLogicalSystem.getName(), activeTheory);
}

StringProcessor &TheoryAssistant::accessPreProcessorPlugin(const unsigned int processorIndex)
{
    const auto processors = activeTheory.getPreFormatter().getProcessors();
    if(processorIndex >= static_cast<uint>(processors.size()))
    {
        throw invalid_argument("There is no processor associated with that index!");
    }

    return *processors[processorIndex];
}

StringProcessor &TheoryAssistant::accessPostProcessorPlugin(const unsigned int processorIndex)
{
    const auto processors = activeTheory.getPostFormatter().getProcessors();
    if(processorIndex >= static_cast<uint>(processors.size()))
    {
        throw invalid_argument("There is no processor associated with that index!");
    }

    return *processors[processorIndex];
}

void TheoryAssistant::addInferenceTacticPlugin(const QString &tacticPluginName)
{
    const auto inferenceTactic = PluginManager::fetchPlugin<const InferenceTactic>(StorageManager::inferenceTacticPluginPath(tacticPluginName));

    auto &theory = activeTheory;
    theory.getInferenceTactics().push_back(inferenceTactic);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.inferenceTacticsPluginsNameList << tacticPluginName;
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

void TheoryAssistant::removeInferenceTacticPlugin(const unsigned int tacticIndex)
{
    auto &theory = activeTheory;
    const auto zeroIndexCompensation = 1;
    if(static_cast<int>(tacticIndex) >= theory.getInferenceTactics().size() - zeroIndexCompensation)
    {
        throw invalid_argument("There is no inference tactic associated with this index!");
    }
    theory.getInferenceTactics().removeAt(tacticIndex);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.inferenceTacticsPluginsNameList.removeAt(tacticIndex);
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

QStringList TheoryAssistant::listLoadedPreProcessors() const
{
    return activeTheory.getPreFormatter().toStringList();
}

QStringList TheoryAssistant::listLoadedPostProcessors() const
{
    return activeTheory.getPostFormatter().toStringList();
}

void TheoryAssistant::createProof(const QString &name, const QString &description, const QStringList &premises, const QString &conclusion) const
{
    //Make Formulas
    const auto parser = activeTheory.getParser();
    const auto premisesFormulas = makePremisesFormulas(premises, parser);
    auto conclusionFormula = parser.parse(conclusion);

    //Proof Id
    const auto activeLogicalSystemName = activeLogicalSystem.getName();
    const auto activeTheoryName = activeTheory.getName();
    const auto currentProofId = StorageManager::retrieveCurrentProofId(activeLogicalSystemName, activeTheoryName);

    //Proof Links
    auto proofsRecords = StorageManager::retrieveProofsRecords(activeLogicalSystemName, activeTheoryName);
    auto premisesLinks = linkPremises(currentProofId, premisesFormulas, proofsRecords);
    auto conclusionLinks = linkConclusion(currentProofId, conclusionFormula, proofsRecords);

    //Create Proof Record
    ProofRecord record(currentProofId, name, description, premisesLinks, conclusionLinks);
    proofsRecords.push_back(record);

    //Create Proof
    const auto proofPluginPath = StorageManager::retrieveLogicalSystemPluginsRecord(activeLogicalSystemName).proofPluginName;
    const auto proof = loadProofPlugin(proofPluginPath,
                                       currentProofId,
                                       name,
                                       description,
                                       premisesFormulas,
                                       conclusionFormula);

    //Store
    const auto proofDataFilePath = StorageManager::proofDataFilePath(activeLogicalSystemName, activeTheoryName, currentProofId);
    const auto newProofId = currentProofId + 1;
    StorageManager::storeProofsRecords(activeLogicalSystemName, activeTheoryName, proofsRecords);
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, *proof);
    StorageManager::storeCurrentProofId(activeLogicalSystemName, activeTheoryName, newProofId);
}

ProofAssistant TheoryAssistant::loadProof(const unsigned int proofId) const
{
    QFile file(StorageManager::proofDataFilePath(activeLogicalSystem.getName(), activeTheory.getName(), proofId));
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    const auto logicalSystemPluginsRecord = retrieveActiveLogicalSystemPluginsRecord();
    const auto proofPluginName = logicalSystemPluginsRecord.getProofPluginName();
    if(proofPluginName == "") //TODO Refactor using a constant
    {
        return ProofAssistant(activeTheory, make_shared<Proof>(stream, activeTheory.getSignature()));
    }
    else
    {
        const auto proofPluginPath = StorageManager::proofPluginPath(proofPluginName);
        auto proof = PluginManager::fetchPlugin(stream, activeTheory.getSignature(), proofPluginPath);
        return ProofAssistant(activeTheory, proof);
    }
}

LogicalSystemPluginsRecord TheoryAssistant::retrieveActiveLogicalSystemPluginsRecord() const
{
    const auto activeSystemName = activeLogicalSystem.getName();
    return StorageManager::retrieveLogicalSystemPluginsRecord(activeSystemName);
}

void TheoryAssistant::saveProof(const ProofAssistant &assistant) const
{
    const auto &proof = assistant.getProof();
    const auto activeLogicalSystemName = activeLogicalSystem.getName();
    const auto activeTheoryName = activeTheory.getName();
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, proof);
}

TheoryPluginsRecord TheoryAssistant::retrieveActiveTheoryPluginsRecord() const
{
    const auto activeSystemName = activeLogicalSystem.getName();
    const auto activeTheoryName = activeTheory.getName();
    return StorageManager::retrieveTheoryPluginsRecord(activeSystemName, activeTheoryName);
}

void TheoryAssistant::storeActiveTheoryPluginsRecord(const TheoryPluginsRecord &pluginsRecord) const
{
    const auto activeSystemName = activeLogicalSystem.getName();
    const auto activeTheoryName = activeTheory.getName();
    StorageManager::storeTheoryPluginsRecord(activeSystemName, activeTheoryName, pluginsRecord);
}

shared_ptr<Proof> TheoryAssistant::loadProofPlugin(const QString &proofPluginName,
                                                   const uint id,
                                                   const QString &name,
                                                   const QString &description,
                                                   const QVector<Formula> &premises,
                                                   const Formula &conclusion) const
{
    if(proofPluginName == "") //TODO Refactor using a constant
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

QVector<Formula> TheoryAssistant::makePremisesFormulas(const QStringList &premises, const Parser &parser) const
{
    QVector<Formula> premisesFormulas;
    for(const auto &formula : premises)
    {
        premisesFormulas.push_back(parser.parse(formula));
    }
    return premisesFormulas;
}

QVector<ProofLinks> TheoryAssistant::linkPremises(const unsigned int currentProofId, const QVector<Formula> &premises, QVector<ProofRecord> &proofsRecords) const
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

ProofLinks TheoryAssistant::linkConclusion(const unsigned int currentProofId, const Formula &conclusion, QVector<ProofRecord> &proofsRecords) const
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

const LogicalSystem &TheoryAssistant::getActiveLogicalSystem() const
{
    return activeLogicalSystem;
}

const ProofPrinter &TheoryAssistant::getProofPrinter() const
{
    return *proofPrinter;
}

