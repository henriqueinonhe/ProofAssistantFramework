#include "logicalsystemrecord.h"

LogicalSystemRecord::LogicalSystemRecord()
{

}

LogicalSystemRecord::LogicalSystemRecord(const QString &name, const QString &description) :
    name(name),
    description(description)
{

}

const QString &LogicalSystemRecord::getName() const
{
    return name;
}

const QString &LogicalSystemRecord::getDescription() const
{
    return description;
}

QDataStream &operator <<(QDataStream &stream, const LogicalSystemRecord &record)
{
    stream << record.name << record.description;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LogicalSystemRecord &record)
{
    stream >> record.name >> record.description;
    return stream;
}


