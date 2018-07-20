#include "logicalsystemrecord.h"

LogicalSystemRecord::LogicalSystemRecord()
{

}

LogicalSystemRecord::LogicalSystemRecord(const QString &name, const QString &description) :
    name(name),
    description(description)
{

}

QString LogicalSystemRecord::getName() const
{
    return name;
}

void LogicalSystemRecord::setName(const QString &value)
{
    name = value;
}

QString LogicalSystemRecord::getDescription() const
{
    return description;
}

void LogicalSystemRecord::setDescription(const QString &value)
{
    description = value;
}

QDataStream &operator <<(QDataStream &stream, const LogicalSystemRecord &record)
{
    stream << record.getName() << record.getDescription();
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LogicalSystemRecord &record)
{
    stream >> record.name >> record.description;
    return stream;
}


