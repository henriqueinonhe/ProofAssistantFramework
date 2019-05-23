#include "proofrecord.h"
#include <QDataStream>
#include "formula.h"

QDataStream &operator <<(QDataStream &stream, const ProofRecord &record)
{
    stream << record.id << record.name << record.description << record.premisesLinks << record.conclusionLinks << record.proofIsDone;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, ProofRecord &record)
{
    stream >> record.id >> record.name >> record.description >> record.premisesLinks >> record.conclusionLinks >> record.proofIsDone;
    return stream;
}

ProofRecord::ProofRecord(QDataStream &stream)
{
    stream >> (*this);
}

ProofRecord::ProofRecord(const unsigned int id, const QString &name, const QString &description, const QVector<ProofLinks> &premisesLinks, const ProofLinks &conclusionLinks) :
    id(id),
    name(name),
    description(description),
    premisesLinks(premisesLinks),
    conclusionLinks(conclusionLinks),
    proofIsDone(false)
{
}

QString ProofRecord::getName() const
{
    return name;
}

void ProofRecord::setName(const QString &value)
{
    name = value;
}

QString ProofRecord::getDescription() const
{
    return description;
}

void ProofRecord::setDescription(const QString &value)
{
    description = value;
}

QStringList ProofRecord::getPremises() const
{
    QStringList premises;
    for(const ProofLinks &link : premisesLinks)
    {
        premises << link.getFormula();
    }

    return premises;
}

QString ProofRecord::getConclusion() const
{
    return conclusionLinks.getFormula();
}

QVector<ProofLinks> ProofRecord::getPremisesLinks() const
{
    return premisesLinks;
}

ProofLinks ProofRecord::getConclusionLinks() const
{
    return conclusionLinks;
}

bool ProofRecord::getProofIsDone() const
{
    return proofIsDone;
}

unsigned int ProofRecord::getId() const
{
    return id;
}
