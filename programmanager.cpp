#include "programmanager.h"
#include "logicalsystemrecord.h"
#include "theoryrecord.h"
#include "storagemanager.h"
#include "theorybuilder.h"
#include "pluginmanager.h"
#include "proofrecord.h"
#include "proof.h"
#include "proofassistant.h"

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
    const QVector<LogicalSystemRecord> records = StorageManager::retrieveLogicalSystemsRecords();
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

Theory *ProgramManager::getActiveTheory() const
{
    checkActiveTheory();
    return activeTheory.get();
}

void ProgramManager::createProof(const QString &name, const QString &description, const QStringList &premises, const QString &conclusion) const
{
    checkActiveTheory();

    //Make Formulas
    const Parser * const parser = activeTheory->parser.get();
    QVector<Formula> premisesFormulas;
    makePremisesFormulas(premises, premisesFormulas, parser);
    Formula conclusionFormula(parser->parse(conclusion));

    //Proof Links
    const QString activeLogicalSystemName = activeLogicalSystem->getName();
    const QString activeTheoryName = activeTheory->getName();
    QVector<ProofRecord> proofsRecords = StorageManager::retrieveProofsRecords(activeLogicalSystemName, activeTheoryName);
    QVector<ProofLinks> premisesLinks;
    linkPremises(premises, proofsRecords, premisesLinks);
    ProofLinks conclusionLinks = linkConclusion(conclusion, proofsRecords);
    //FIXME! We should also retroactively link previously stored proof links! They are reciprocal!

    //Proof Id
    const unsigned int currentId = StorageManager::retrieveCurrentProofId(activeLogicalSystemName, activeTheoryName);

    //Create Proof Record
    ProofRecord record(currentId, name, description, premisesLinks, conclusionLinks);
    proofsRecords.push_back(record);

    //Create Proof
    Proof proof(currentId, name, description, premisesFormulas, conclusionFormula);

    //Store
    const QString proofDataFilePath = StorageManager::proofDataFilePath(activeLogicalSystemName, activeTheoryName, currentId);
    const unsigned int newId = currentId + 1;
    StorageManager::storeProofsRecords(activeLogicalSystemName, activeTheoryName, proofsRecords);
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, proof);
    StorageManager::storeCurrentProofId(activeLogicalSystemName, activeTheoryName, newId);
}

ProofAssistant ProgramManager::loadProof(const unsigned int proofId) const
{
    checkActiveTheory();

    QFile file(StorageManager::proofDataFilePath(activeLogicalSystem->getName(), activeTheory->getName(), proofId));
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    return ProofAssistant(activeTheory.get(), Proof(stream, activeTheory->getSignature().get()));
}

void ProgramManager::saveProof(const ProofAssistant &assistant) const
{
    const Proof proof = assistant.getProof();
    const QString activeLogicalSystemName = activeLogicalSystem->getName();
    const QString activeTheoryName = activeTheory->getName();
    StorageManager::storeProofData(activeLogicalSystemName, activeTheoryName, proof);
}

void ProgramManager::createTheory(const TheoryBuilder &builder, const TheoryPluginsRecord &pluginsRecord) const
{
    //NOTE Maybe we should check signature compliance here
    checkActiveLogicalSystem();

    const QString theoryName = builder.getName();
    const QString theoryDescription = builder.getDescription();

    //Theory Name Collision
    const QString activeLogicalSystemName = activeLogicalSystem->getName();
    if(checkTheoryNameCollision(activeLogicalSystemName, theoryName))
    {
        throw std::invalid_argument("There already exists a theory with this name!");
    }

    //Theory
    const Theory theory = builder.build();

    //TheoryRecord
    TheoryRecord newTheoryRecord(theoryName, theoryDescription);
    QVector<TheoryRecord> records = StorageManager::retrieveTheoriesRecords(activeLogicalSystemName);
    records.append(newTheoryRecord);

    //File Management
    StorageManager::storeTheoriesRecords(activeLogicalSystemName, records);
    StorageManager::setupTheoryDir(activeLogicalSystemName, theory, pluginsRecord);
}

void ProgramManager::removeTheory(const QString &theoryName) const
{
    checkActiveLogicalSystem();
    const QString logicalSystemName = activeLogicalSystem->getName();
    if(!checkTheoryNameCollision(logicalSystemName, theoryName))
    {
        QString errorMsg;
        errorMsg += "There is no theory named: \"";
        errorMsg += theoryName + "\".";

        throw std::invalid_argument(errorMsg.toStdString());
    }

    QVector<TheoryRecord> newRecords = getTheoryRecordsWithoutRemovedRecord(logicalSystemName, theoryName);
    StorageManager::storeTheoriesRecords(logicalSystemName, newRecords);

    StorageManager::deleteTheoryDir(logicalSystemName,theoryName);
}

bool ProgramManager::checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const
{
    const QVector<TheoryRecord> records = StorageManager::retrieveTheoriesRecords(logicalSystemName);
    return std::any_of(records.begin(), records.end(), [&name](const TheoryRecord &record)
    {
        return record.getName() == name;
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

void ProgramManager::loadInferenceRules(const QStringList &inferenceRulesNames, QVector<shared_ptr<const InferenceRule> > &inferenceRules) const
{
    QStringList inferenceRulesPathList = StorageManager::convertPluginNamesToPaths(inferenceRulesNames, StorageManager::inferenceRulePluginPath);
    inferenceRules = PluginManager::fetchPluginVector<const InferenceRule>(inferenceRulesPathList);
}

void ProgramManager::makePremisesFormulas(const QStringList &premises, QVector<Formula> &premisesFormulas, const Parser *parser) const
{
    for(const QString &formula : premises)
    {
        premisesFormulas.push_back(parser->parse(formula));
    }
}

void ProgramManager::linkPremises(const QStringList &premises, const QVector<ProofRecord> &proofsRecords, QVector<ProofLinks> &premisesLinks) const
{
    for(const QString &premiss : premises)
    {
        QVector<unsigned int> linkedProofsIds;
        for(const ProofRecord &record : proofsRecords)
        {
            if(premiss == record.getConclusion())
            {
                linkedProofsIds.push_back(record.getId());
            }
        }
        premisesLinks.push_back(ProofLinks(premiss, linkedProofsIds));
    }
}

ProofLinks ProgramManager::linkConclusion(const QString &conclusion, const QVector<ProofRecord> &proofsRecords) const
{
    QVector<unsigned int> linkedProofsIds;
    for(const ProofRecord &record : proofsRecords)
    {
        for(const QString &premiss : record.getPremises())
        {
            if(conclusion == premiss)
            {
                linkedProofsIds.push_back(record.getId());
                break;
            }
        }
    }
    return ProofLinks(conclusion, linkedProofsIds);
}

void ProgramManager::createLogicalSystem(const QString &name,
                                         const QString &description,
                                         const QStringList &inferenceRulesNamesList,
                                         const Type &wffType) const
{
    if(checkLogicalSystemNameCollision(name))
    {
        throw std::invalid_argument("There already exists a logical system with this name!");
    }

    //Logical System
    QVector<shared_ptr<const InferenceRule>> inferenceRules;;
    loadInferenceRules(inferenceRulesNamesList, inferenceRules);
    LogicalSystem logicalSystem(name, description, inferenceRules, wffType); //If Logical System creation is unsuccesfull for whatever reason (like problems loading plugins) it will throw an exception and the directories and records creation won't be carried out

    //LogicalSystemRecord
    LogicalSystemRecord newSystemRecord(name, description);
    QVector<LogicalSystemRecord> records = StorageManager::retrieveLogicalSystemsRecords();
    records.append(newSystemRecord);

    //File management
    StorageManager::storeLogicalSystemsRecords(records);
    StorageManager::setupLogicalSystemDir(logicalSystem, inferenceRulesNamesList);
}

QVector<LogicalSystemRecord> ProgramManager::getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const
{
    const QVector<LogicalSystemRecord> oldRecords = StorageManager::retrieveLogicalSystemsRecords();
    QVector<LogicalSystemRecord> newRecords;

    std::for_each(oldRecords.begin(), oldRecords.end(), [&newRecords, &name](const LogicalSystemRecord &record)
    {
        if(record.getName() != name)
        {
            newRecords.append(record);
        }
    });

    return newRecords;
}

QVector<TheoryRecord> ProgramManager::getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const
{
    const QVector<TheoryRecord> oldRecords = StorageManager::retrieveTheoriesRecords(logicalSystemName);
    QVector<TheoryRecord> newRecords;

    std::for_each(oldRecords.begin(), oldRecords.end(), [&newRecords, &theoryName](const TheoryRecord &record)
    {
        if(record.getName() != theoryName)
        {
            newRecords.append(record);
        }
    });

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

    QVector<LogicalSystemRecord> newRecords = getLogicalSystemRecordsWithoutRemovedRecord(name);
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
    activeLogicalSystem == nullptr;
}


