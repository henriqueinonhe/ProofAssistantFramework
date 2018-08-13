#include "logicalsystem.h"

LogicalSystem::LogicalSystem()
{

}

LogicalSystem::LogicalSystem(const QString &name, const QString &description, const QVector<const InferenceRule *> inferenceRules, const Type &wffType) :
    name(name),
    description(description),
    inferenceRules(inferenceRules),
    wffType(new Type(wffType))
{
}

LogicalSystem::LogicalSystem(QDataStream &stream, QVector<const InferenceRule *> &inferenceRules)
{
    stream >> name >> description;
    wffType.reset(new Type(stream));
    this->inferenceRules = inferenceRules;
}

void LogicalSystem::serialize(QDataStream &stream) const
{
    stream << name << description << *wffType;
}

QString LogicalSystem::getName() const
{
    return name;
}

void LogicalSystem::setName(const QString &value)
{
    name = value;
}


QVector<const InferenceRule *> LogicalSystem::getInferenceRules() const
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



QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem)
{
    logicalSystem.serialize(stream);

    return stream;
}
