#ifndef PROOFLINKS_H
#define PROOFLINKS_H

#include "formula.h"

using namespace std;

class Proof;

class ProofLinks
{
public:
    //ProofLinks(const Formula &formula, const QVector<unsigned int> linkedProofsIds);

    Formula getFormula() const;

private:
//    Formula formula;
//    QVector<unsigned int> linkedProofsIds;

    friend QDataStream &operator <<(QDataStream &stream, const ProofLinks &links);
    friend QDataStream &operator >>(QDataStream &stream, ProofLinks &links);
};

QDataStream &operator <<(QDataStream &stream, const ProofLinks &links);
QDataStream &operator >>(QDataStream &stream, ProofLinks &links);


#endif // PROOFLINKS_H
