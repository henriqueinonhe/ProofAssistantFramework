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

const QString &TheoryRecord::getName() const
{
    return name;
}

const QString &TheoryRecord::getDescription() const
{
    return description;
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
