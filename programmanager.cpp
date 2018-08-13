#include "programmanager.h"

ProgramManager::ProgramManager() :
    activeLogicalSystem(nullptr),
    activeTheory(nullptr)
{

}

LogicalSystem *ProgramManager::getActiveLogicalSystem() const
{
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
    Theory *theory = new Theory(activeLogicalSystem.get()); //FIXME Use smart ptr!
    StorageManager::loadTheory(activeLogicalSystem->getName(), name, *theory);
    activeTheory.reset(theory);
}

Theory *ProgramManager::getActiveTheory() const
{
    return activeTheory.get();
}

void ProgramManager::createTheory(const QString &name, const QString &description, const QLinkedList<Formula> axioms, const QStringList &inferenceTacticsPluginsNameList, const QStringList &preProcessorPluginsNameList, const QStringList &postProcessorPluginsNameList) const
{
    checkActiveLogicalSystem();
    const QString activeLogicalSystemName = activeLogicalSystem->getName();
    if(checkTheoryNameCollision(activeLogicalSystemName, name))
    {
        throw std::invalid_argument("There already exists a theory with this name!");
    }


    //TheoryRecord
    TheoryRecord newTheoryRecord(name, description);
    QVector<TheoryRecord> records = StorageManager::retrieveTheoriesRecords(activeLogicalSystemName);
    records.append(newTheoryRecord);

    //File Management
    StorageManager::storeTheoriesRecords(activeLogicalSystemName, records);
//    StorageManager::createTheoryDir(activeLogicalSystemName, Theory(activeLogicalSystem.get(),
//                                                                    name,
//                                                                    description,
//                                                                    axioms,
//                                                                    activeLogicalSystem->getSignaturePluginName(),
//                                                                    inferenceTacticsPluginsNameList,
//                                                                    preProcessorPluginsNameList,
//                                                                    postProcessorPluginsNameList)); FIXME!
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

void ProgramManager::createLogicalSystem(const QString &name,
                                         const QString &description,
                                         const QString &signaturePluginName,
                                         const QStringList &inferenceRuleNamesList,
                                         const Type &wffType) const
{
    if(checkLogicalSystemNameCollision(name))
    {
        throw std::invalid_argument("There already exists a logical system with this name!");
    }

    //TODO Refactor
    //LogicalSystemRecord
    LogicalSystemRecord newSystemRecord(name, description);
    QVector<LogicalSystemRecord> records = StorageManager::retrieveLogicalSystemsRecords();
    records.append(newSystemRecord);

    //File management
    StorageManager::storeLogicalSystemsRecords(records);
//    StorageManager::createLogicalSystemDir(LogicalSystem(name, description, signaturePluginName, inferenceRuleNamesList, wffType)); FIXME!

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
    LogicalSystem *system = new LogicalSystem;
    StorageManager::loadLogicalSystem(name, *system);

    activeLogicalSystem.reset(system);
    //system->loadInferenceRules(); //FIXME!
}















