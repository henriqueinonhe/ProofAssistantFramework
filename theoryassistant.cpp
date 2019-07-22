#include "theoryassistant.h"
#include "storagemanager.h"
#include "pluginmanager.h"
#include "theorypluginsrecord.h"
#include "proofrecord.h"
#include "proofassistant.h"
#include "parser.h"

TheoryAssistant::TheoryAssistant(const LogicalSystem &activeLogicalSystem, Theory &&activeTheory) :
    activeLogicalSystem(activeLogicalSystem),
    activeTheory(std::move(activeTheory))
{

}

const Theory &TheoryAssistant::getActiveTheory() const
{
    return activeTheory;
}

Signature &TheoryAssistant::accessSignaturePlugin()
{
    return *activeTheory.getSignature();
}

void TheoryAssistant::addPreProcessorPlugin(const QString &processorPluginName)
{
    const auto processor = PluginManager::fetchPlugin<StringProcessor>(StorageManager::preProcessorPluginPath(processorPluginName));

    auto &theory = activeTheory;
    theory.getPreFormatter().addProcessor(processor);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.preProcessorsPluginsNameList << processorPluginName;
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

void TheoryAssistant::addPostProcessorPlugin(const QString &processorPluginName)
{
    checkActiveTheory();
    const auto processor = PluginManager::fetchPlugin<StringProcessor>(StorageManager::postProcessorPluginPath(processorPluginName));

    auto &theory = *activeTheory;
    theory.getPostFormatter().addProcessor(processor);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.postProcessorsPluginsNameList << processorPluginName;
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

void TheoryAssistant::removePreProcessorPlugin(const unsigned int processorIndex) const
{
    checkActiveTheory();
    auto &theory = *activeTheory;
    theory.getPreFormatter().removeProcessor(processorIndex);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.preProcessorsPluginsNameList.pop_back();
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

void TheoryAssistant::removePostProcessorPlugin(const unsigned int processorIndex) const
{
    checkActiveTheory();
    auto &theory = *activeTheory;
    theory.getPostFormatter().removeProcessor(processorIndex);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.postProcessorsPluginsNameList.pop_back();
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

void TheoryAssistant::addInferenceTacticPlugin(const QString &tacticPluginName) const
{
    checkActiveTheory();
    const auto inferenceTactic = PluginManager::fetchPlugin<const InferenceTactic>(StorageManager::inferenceTacticPluginPath(tacticPluginName));

    auto &theory = *activeTheory;
    theory.getInferenceTactics().push_back(inferenceTactic);

    auto pluginsRecord = retrieveActiveTheoryPluginsRecord();
    pluginsRecord.inferenceTacticsPluginsNameList << tacticPluginName;
    storeActiveTheoryPluginsRecord(pluginsRecord);
}

void TheoryAssistant::removeInferenceTacticPlugin(const unsigned int tacticIndex) const
{
    checkActiveTheory();
    auto &theory = *activeTheory;
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

void TheoryAssistant::createProof(const QString &name, const QString &description, const QStringList &premises, const QString &conclusion) const
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
    checkActiveTheory();

    QFile file(StorageManager::proofDataFilePath(activeLogicalSystem->getName(), activeTheory->getName(), proofId));
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    const auto logicalSystemPluginsRecord = retrieveActiveLogicalSystemPluginsRecord();
    const auto proofPluginName = logicalSystemPluginsRecord.getProofPluginName();
    if(proofPluginName == defaultProofPluginName)
    {
        return ProofAssistant(activeTheory.get(), make_shared<Proof>(stream, activeTheory->getSignature()));
    }
    else
    {
        const auto proofPluginPath = StorageManager::proofPluginPath(proofPluginName);
        auto proof = PluginManager::fetchPlugin<Proof>(proofPluginPath, stream);
        return ProofAssistant(activeTheory.get(), proof);
    }
}

void TheoryAssistant::saveProof(const ProofAssistant &assistant) const
{
    const auto &proof = assistant.getProof();
    const auto activeLogicalSystemName = activeLogicalSystem->getName();
    const auto activeTheoryName = activeTheory->getName();
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, proof);
}

TheoryPluginsRecord TheoryAssistant::retrieveActiveTheoryPluginsRecord() const
{
    checkActiveTheory();
    const auto activeSystemName = activeLogicalSystem->getName();
    const auto activeTheoryName = activeTheory->getName();
    return StorageManager::retrieveTheoryPluginsRecord(activeSystemName, activeTheoryName);
}

void TheoryAssistant::storeActiveTheoryPluginsRecord(const TheoryPluginsRecord &pluginsRecord) const
{
    checkActiveTheory();
    const auto activeSystemName = activeLogicalSystem->getName();
    const auto activeTheoryName = activeTheory->getName();
    StorageManager::storeTheoryPluginsRecord(activeSystemName, activeTheoryName, pluginsRecord);
}

shared_ptr<Proof> TheoryAssistant::loadProofPlugin(const QString &proofPluginName,
                                                  const uint id,
                                                  const QString &name,
                                                  const QString &description,
                                                  const QVector<Formula> &premises,
                                                  const Formula &conclusion) const
{
    if(proofPluginName == defaultProofPluginName)
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

QVector<Formula> TheoryAssistant::makePremisesFormulas(const QStringList &premises, const Parser *parser) const
{
    QVector<Formula> premisesFormulas;
    for(const auto &formula : premises)
    {
        premisesFormulas.push_back(parser->parse(formula));
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

