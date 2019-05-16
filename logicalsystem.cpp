#include "logicalsystem.h"
#include "storagemanager.h"
#include "containerauxiliarytools.h"

LogicalSystem::LogicalSystem(const QString &name, const QString &description, const QVector<const InferenceRule *> &inferenceRules, const Type &wffType) :
    name(name),
    description(description),
    wffType(new Type(wffType))
{
    ContainerAuxiliaryTools::adaptToSmartPointerContainer(inferenceRules, this->inferenceRules);
}

LogicalSystem::LogicalSystem(QDataStream &stream, const QVector<const InferenceRule *> &inferenceRules)
{
    stream >> *this;
    ContainerAuxiliaryTools::adaptToSmartPointerContainer(inferenceRules, this->inferenceRules);
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
