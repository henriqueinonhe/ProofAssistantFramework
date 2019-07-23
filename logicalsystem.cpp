#include "logicalsystem.h"
#include "storagemanager.h"
#include "containerauxiliarytools.h"
#include "qtclassesdeserialization.h"

LogicalSystem::LogicalSystem(const QString &name, const QString &description, const QVector<shared_ptr<const InferenceRule>> &inferenceRules, const Type &wffType) :
    name(name),
    description(description),
    inferenceRules(inferenceRules),
    wffType(wffType)
{
}

LogicalSystem::LogicalSystem(QDataStream &stream, const QVector<shared_ptr<const InferenceRule> > &inferenceRules) :
    name(QtDeserialization::deserializeQString(stream)),
    description(QtDeserialization::deserializeQString(stream)),
    inferenceRules(inferenceRules),
    wffType(stream)
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


QVector<shared_ptr<const InferenceRule> > LogicalSystem::getInferenceRules() const
{
    return inferenceRules;
}

Type LogicalSystem::getWffType() const
{
    return wffType;
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
    stream << logicalSystem.name << logicalSystem.description << logicalSystem.wffType;

    return stream;
}
