#include "proofrecord.h"
#include <QDataStream>

ProofRecord::ProofRecord()
{

}

QDataStream &operator <<(QDataStream &stream, const ProofRecord &record)
{
    stream << record.name << record.description << record.premises << record.conclusion;

    return stream;
}

QDataStream &operator >>(QDataStream &stream, ProofRecord &record)
{
    stream >> record.name >> record.description >> record.premises >> record.conclusion;

    return stream;
}
