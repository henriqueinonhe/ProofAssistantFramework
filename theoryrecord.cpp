#include "theoryrecord.h"
#include <QDataStream>

TheoryRecord::TheoryRecord()
{

}

TheoryRecord::TheoryRecord(const QString &name, const QString &description) :
    name(name),
    description(description)
{

}

QString TheoryRecord::getName() const
{
    return name;
}

void TheoryRecord::setName(const QString &value)
{
    name = value;
}

QString TheoryRecord::getDescription() const
{
    return description;
}

void TheoryRecord::setDescription(const QString &value)
{
    description = value;
}

QDataStream &operator <<(QDataStream &stream, const TheoryRecord &record)
{
    stream << record.name << record.description;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, TheoryRecord &record)
{
    stream >> record.name >> record.description;
    return stream;
}
