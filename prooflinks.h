#ifndef PROOFLINKS_H
#define PROOFLINKS_H

#include "formula.h"

using namespace std;

class Proof;

class ProofLinks
{
public:
    ProofLinks();

    const Formula *getFormula() const;
    void setFormula(const Formula * const value);

    QVector<const Proof *> getLinks() const;

private:
    const Formula *formula; //Maybe this should just be an ordinary pointer after all... I mean, the great question is... Should this own the object? Considering it won't change anyways and if it does a new proof link oughta be created...
    QVector<const Proof *> links;
};


#endif // PROOFLINKS_H
