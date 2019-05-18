#include "prooflinks.h"
#include <QDataStream>

//ProofLinks::ProofLinks(const Formula &formula, const QVector<unsigned int> linkedProofsIds) :
//    formula(formula),
//    linkedProofsIds(linkedProofsIds)
//{

//}

//Formula ProofLinks::getFormula() const
//{
//    return formula;
//}

QDataStream &operator <<(QDataStream &stream, const ProofLinks &links)
{
    //TODO
}

QDataStream &operator >>(QDataStream &stream, ProofLinks &links)
{
    //TODO
}
