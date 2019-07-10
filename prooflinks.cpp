#include "prooflinks.h"
#include <QDataStream>

ProofLinks::ProofLinks(QDataStream &stream)
{
    stream >> *this;
}

ProofLinks::ProofLinks(const QString &formula, const QVector<unsigned int> linkedProofsIds) :
    formula(formula),
    linkedProofsIds(linkedProofsIds)
{
}

QString ProofLinks::getFormula() const
{
    return formula;
}

QVector<unsigned int> ProofLinks::getLinkedProofsIds() const
{
    return linkedProofsIds;
}

void ProofLinks::addLinkedProofId(const unsigned int id)
{
    linkedProofsIds.push_back(id);
}

bool ProofLinks::operator==(const ProofLinks &other) const
{
    return getFormula() == other.formula &&
           getLinkedProofsIds() == other.linkedProofsIds;
}

bool ProofLinks::operator!=(const ProofLinks &other) const
{
    return !((*this) == other);
}

ProofLinks::ProofLinks()
{

}

QDataStream &operator <<(QDataStream &stream, const ProofLinks &links)
{
    stream << links.formula << links.linkedProofsIds;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, ProofLinks &links)
{
    stream >> links.formula >> links.linkedProofsIds;
    return stream;
}


QDataStream &operator >>(QDataStream &stream, QVector<ProofLinks> &vec)
{
    int size;
    stream >> size;
    for(int i = 0; i < size; i++)
    {
        vec.push_back(ProofLinks(stream));
    }
    return stream;
}
