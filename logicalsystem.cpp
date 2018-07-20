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
    std::for_each(inferenceRulesPluginsNames.begin(), inferenceRulesPluginsNames.end(), [this](const QString &pluginName)
    {
        QString inferenceRulePluginPath = inferenceRulesPluginsDirPath + "/" + pluginName;

        QPluginLoader loader;
        loader.setFileName(inferenceRulePluginPath);
        bool loadSuccess = loader.load();

        if(!loadSuccess)
        {
            throw std::runtime_error(""); //Create specialized exception
        }

        inferenceRules.push_back(qobject_cast<InferenceRule *>(loader.instance()));
    });
}

QString LogicalSystem::getInferenceRulesPluginsDirPath() const
{
    return inferenceRulesPluginsDirPath;
}

void LogicalSystem::setInferenceRulesPluginsDirPath(const QString &value)
{
    inferenceRulesPluginsDirPath = value;
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
    QString wffTypeRawString = system.getWffType().toString();

    stream << system.name << system.description << system.inferenceRulesPluginsNames << wffTypeRawString;

    return stream;
}

QDataStream & operator >>(QDataStream &stream, LogicalSystem &system)
{
    QString wffTypeRawString;

    stream >> system.name >> system.description >> system.inferenceRulesPluginsNames >> wffTypeRawString;
    system.setWffType(wffTypeRawString);

    return stream;
}
