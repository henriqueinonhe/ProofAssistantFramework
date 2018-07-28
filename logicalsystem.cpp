#include "logicalsystem.h"

LogicalSystem::LogicalSystem()
{

}

LogicalSystem::LogicalSystem(const QString &name, const QString &description, const QStringList &inferenceRulesPluginsNames, const Type &wffType) :
    name(name),
    description(description),
    inferenceRulesPluginsNames(inferenceRulesPluginsNames),
    wffType(new Type(wffType))
{

}

QString LogicalSystem::getName() const
{
    return name;
}

void LogicalSystem::setName(const QString &value)
{
    name = value;
}

QStringList LogicalSystem::getInferenceRulesPluginsNames() const
{
    return inferenceRulesPluginsNames;
}

void LogicalSystem::setInferenceRulesPluginsNames(const QStringList &value)
{
    inferenceRulesPluginsNames = value;
}

void LogicalSystem::addInferenceRulePluginName(const QString &pluginName)
{
    inferenceRulesPluginsNames.push_back(pluginName);
}

void LogicalSystem::loadInferenceRules()
{
    PluginManager::loadPluginVector<InferenceRule>(inferenceRules,
                                                   inferenceRulesPluginsNames,
                                                   StorageManager::inferenceRulePluginPath);
}

QVector<InferenceRule *> LogicalSystem::getInferenceRules() const
{
    return inferenceRules;
}

Type LogicalSystem::getWffType() const
{
    return *wffType;
}

void LogicalSystem::setWffType(const Type &value)
{
    wffType.reset(new Type(value));
}

QString LogicalSystem::getDescription() const
{
    return description;
}

void LogicalSystem::setDescription(const QString &value)
{
    description = value;
}


QDataStream & operator <<(QDataStream &stream, const LogicalSystem &system)
{
    stream << system.name << system.description << system.inferenceRulesPluginsNames << system.getWffType();

    return stream;
}

QDataStream & operator >>(QDataStream &stream, LogicalSystem &system)
{
    stream >> system.name >> system.description >> system.inferenceRulesPluginsNames;
    system.setWffType(Type(stream));

    return stream;
}
