#include "logicalsystem.h"

LogicalSystem::LogicalSystem()
{

}

LogicalSystem::LogicalSystem(const QString &name, const QString &description, const Type &wffType) :
    name(name),
    description(description),
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
    stream << system.name << system.description << system.getWffType();

    return stream;
}

QDataStream & operator >>(QDataStream &stream, LogicalSystem &system)
{
    stream >> system.name >> system.description ;
    system.setWffType(Type(stream));

    return stream;
}
