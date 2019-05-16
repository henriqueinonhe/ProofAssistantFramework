#include "logicalsystem.h"
#include "storagemanager.h"

LogicalSystem::LogicalSystem(const QString &name, const QString &description, QStringList inferenceRulesNamesList, const QString &signatureName, const Type &wffType) :
    name(name),
    description(description),
    signatureName(signatureName),
    wffType(new Type(wffType))
{
    loadInferenceRuleList(inferenceRulesNamesList);
}

LogicalSystem::LogicalSystem(QDataStream &stream)
{
    stream >> *this;
}

void LogicalSystem::serialize(QDataStream &stream) const
{
    stream << name << description << inferenceRules << signatureName << *wffType;
}

QString LogicalSystem::getName() const
{
    return name;
}

void LogicalSystem::setName(const QString &value)
{
    name = value;
}


QVector<InferenceRulePlugin> LogicalSystem::getInferenceRules() const
{
    return inferenceRules;
}

Type LogicalSystem::getWffType() const
{
    return *wffType;
}

QString LogicalSystem::getDescription() const
{
    return description;
}

void LogicalSystem::setDescription(const QString &value)
{
    description = value;
}

void LogicalSystem::loadInferenceRuleList(const QStringList &inferenceRulesNamesList)
{
    for(int index = 0; index < inferenceRulesNamesList.size(); index++)
    {
        const QString inferenceRulePluginPath = StorageManager::inferenceRulePluginPath(inferenceRulesNamesList[index]);
        InferenceRulePlugin plugin(inferenceRulePluginPath);
        inferenceRules.push_back(plugin);
    }
}

QString LogicalSystem::getSignatureName() const
{
    return signatureName;
}

LogicalSystem::LogicalSystem()
{

}

QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem)
{
    stream >> logicalSystem.name >> logicalSystem.description >> logicalSystem.inferenceRules >> logicalSystem.signatureName;
    logicalSystem.wffType.reset(new Type(stream));

    return stream;
}


QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem)
{
    logicalSystem.serialize(stream);

    return stream;
}
