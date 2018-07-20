#include "programmanager.h"

ProgramManager::ProgramManager()
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

void ProgramManager::createLogicalSystem(const QString &name,
                                         const QString &description,
                                         const QStringList &inferenceRuleNamesList) const
{
    if(checkLogicalSystemNameCollision(name))
    {
        throw std::invalid_argument("There already exists a logical system with that name!");
    }

    LogicalSystemRecord newSystemRecord(name, description);
    QVector<LogicalSystemRecord> records = StorageManager::retrieveLogicalSystemsRecords();
    records.append(newSystemRecord);

    StorageManager::storeLogicalSystemsRecords(records);
    StorageManager::createLogicalSystemDir(LogicalSystem(name, description, inferenceRuleNamesList));
}

QVector<LogicalSystemRecord> ProgramManager::getLogicalSystemRecordsWithoutRemovedRecord(const QString &name) const
{
    QVector<LogicalSystemRecord> oldRecords = StorageManager::retrieveLogicalSystemsRecords();
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
    StorageManager::loadLogicalSystem(name, system);

    activeLogicalSystem.reset(system);
}















