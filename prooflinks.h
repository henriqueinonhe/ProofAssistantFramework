#ifndef PROOFLINKS_H
#define PROOFLINKS_H

#include "formula.h"

using namespace std;

class Proof;

class ProofLinks
{
public:
    ProofLinks();

    Formula getFormula() const;

private:
    Formula formula;
    QVector<unsigned int> linkedProofsIds;
};


#endif // PROOFLINKS_H
