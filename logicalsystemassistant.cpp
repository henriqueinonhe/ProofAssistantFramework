#include "logicalsystemassistant.h"
#include "storagemanager.h"
#include "theorybuilder.h"
#include "logicalsystem.h"
#include "theoryrecord.h"
#include "logicalsystempluginsrecord.h"
#include "pluginmanager.h"

const LogicalSystem &LogicalSystemAssistant::getActiveLogicalSystem() const
{
    return activeLogicalSystem;
}

void LogicalSystemAssistant::loadTheory(const QString &name)
{
    checkActiveLogicalSystem();
    Theory *theory = nullptr;
    StorageManager::loadTheory(activeLogicalSystem, name, theory);
    //Return TheoryAssistant
}

void LogicalSystemAssistant::createTheory(const TheoryBuilder &builder, const TheoryPluginsRecord &pluginsRecord) const
{
    checkActiveLogicalSystem();

    const auto theoryName = builder.getName();
    const auto theoryDescription = builder.getDescription();

    //Theory Name Collision
    const auto activeLogicalSystemName = activeLogicalSystem.getName();
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

void LogicalSystemAssistant::removeTheory(const QString &theoryName) const
{
    checkActiveLogicalSystem();
    const auto logicalSystemName = activeLogicalSystem.getName();
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

bool LogicalSystemAssistant::checkTheoryNameCollision(const QString &logicalSystemName, const QString &name) const
{
    const auto records = StorageManager::retrieveTheoriesRecords(logicalSystemName);
    return std::any_of(records.begin(), records.end(), [&name](const TheoryRecord &record)
    {
        return record.name == name;
    });
}

void LogicalSystemAssistant::checkActiveLogicalSystem() const
{
    if(activeLogicalSystem == nullptr)
    {
        throw std::invalid_argument("There is currently no active logical system!");
    }
}

LogicalSystemPluginsRecord LogicalSystemAssistant::retrieveActiveLogicalSystemPluginsRecord() const
{
    checkActiveLogicalSystem();
    const auto activeSystemName = activeLogicalSystem.getName();
    return StorageManager::retrieveLogicalSystemPluginsRecord(activeSystemName);
}

void LogicalSystemAssistant::storeActiveLogicalSystemPluginsRecord(const LogicalSystemPluginsRecord &pluginsRecord) const
{
    checkActiveLogicalSystem();
    const auto activeSystemName = activeLogicalSystem.getName();
    StorageManager::storeLogicalSystemPluginsRecord(activeSystemName, pluginsRecord);
}

shared_ptr<Signature> LogicalSystemAssistant::loadSignature(const QString &signatureName) const
{
    auto signaturePath = StorageManager::signaturePluginPath(signatureName);
    return PluginManager::fetchPlugin<Signature>(signaturePath);
}

QVector<TheoryRecord> LogicalSystemAssistant::getTheoryRecordsWithoutRemovedRecord(const QString &logicalSystemName, const QString &theoryName) const
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

LogicalSystemAssistant::LogicalSystemAssistant(LogicalSystem &&logicalSystem) :
    activeLogicalSystem(std::move(logicalSystem))
{
}


