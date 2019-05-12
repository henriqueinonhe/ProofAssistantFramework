#include "logicalsystem.h"
#include "pluginmanager.h"

LogicalSystem::LogicalSystem(const QString &name, const QString &description, QStringList inferenceRulesNamesList, const QString &signatureName, const Type &wffType) :
    name(name),
    description(description),
    inferenceRulesNamesList(inferenceRulesNamesList),
    signatureName(signatureName),
    wffType(new Type(wffType))
{
    loadInferenceRuleList();
}

LogicalSystem::LogicalSystem(QDataStream &stream)
{
    stream >> *this;
}

void LogicalSystem::serialize(QDataStream &stream) const
{
    stream << name << description << inferenceRulesNamesList << signatureName << *wffType;
}

QString LogicalSystem::getName() const
{
    return name;
}

void LogicalSystem::setName(const QString &value)
{
    name = value;
}


QVector<InferenceRule *> LogicalSystem::getInferenceRules() const
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

void LogicalSystem::loadInferenceRuleList()
{
    PluginManager::loadPluginVector(inferenceRules, inferenceRulesNamesList, StorageManager::inferenceRulePluginPath);
//    QString path = StorageManager::inferenceRulePluginPath("LogosClassicAndElimination");
//    QPluginLoader loader(path);
//    bool b = loader.load();

//    const InferenceRule *ptr = qobject_cast<InferenceRule *>(loader.instance());
//    std::cout << ptr->name().toStdString();
    //    std::cout << ptr->callCommand().toStdString();
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
    stream >> logicalSystem.name >> logicalSystem.description >> logicalSystem.inferenceRulesNamesList >> logicalSystem.signatureName;
    logicalSystem.wffType.reset(new Type(stream));
    logicalSystem.loadInferenceRuleList();

    return stream;
}


QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem)
{
    logicalSystem.serialize(stream);

    return stream;
}
