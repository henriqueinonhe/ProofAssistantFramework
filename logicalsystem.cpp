#include "logicalsystem.h"
#include "storagemanager.h"
#include "containerauxiliarytools.h"

LogicalSystem::LogicalSystem(const QString &name, const QString &description, const QVector<shared_ptr<const InferenceRule>> &inferenceRules, const Type &wffType) :
    name(name),
    description(description),
    inferenceRules(inferenceRules),
    wffType(new Type(wffType))
{
}

LogicalSystem::LogicalSystem(QDataStream &stream, const QVector<shared_ptr<const InferenceRule> > &inferenceRules) :
    inferenceRules(inferenceRules)
{
    stream >> *this;
}

const QString &LogicalSystem::getName() const
{
    return name;
}

void LogicalSystem::setName(const QString &value)
{
    name = value;
}


const QVector<shared_ptr<const InferenceRule> > &LogicalSystem::getInferenceRules() const
{
    return inferenceRules;
}

const Type &LogicalSystem::getWffType() const
{
    return *wffType;
}

const QString &LogicalSystem::getDescription() const
{
    return description;
}

void LogicalSystem::setDescription(const QString &value)
{
    description = value;
}


QDataStream &operator >>(QDataStream &stream, LogicalSystem &logicalSystem)
{
    stream >> logicalSystem.name >> logicalSystem.description;
    logicalSystem.wffType.reset(new Type(stream));

    return stream;
}


QDataStream &operator <<(QDataStream &stream, const LogicalSystem &logicalSystem)
{
    stream << logicalSystem.name << logicalSystem.description << *logicalSystem.wffType;

    return stream;
}
