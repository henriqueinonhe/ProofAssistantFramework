#ifndef PROOFLINKS_H
#define PROOFLINKS_H

#include "formula.h"

using namespace std;

class Proof;

class ProofLinks
{
public:
    ProofLinks();

private:
    unique_ptr<Formula> formula; //Maybe this should just be an ordinary pointer after all... I mean, the great question is... Should this own the object? Considering it won't change anyways and if it does a new proof link oughta be created...
    QVector<Proof *> links;
};

#endif // PROOFLINKS_H
