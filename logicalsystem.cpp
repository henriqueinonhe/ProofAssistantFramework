#include "logicalsystem.h"

LogicalSystem::LogicalSystem()
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

        shared_ptr<InferenceRule> inferenceRulePtr;
        inferenceRulePtr.reset(qobject_cast<InferenceRule *>(loader.instance()));

        inferenceRules.push_back(inferenceRulePtr);
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
