#ifndef PROOFLINKS_H
#define PROOFLINKS_H

#include "formula.h"

using namespace std;

class Proof;

class ProofLinks
{
public:
    ProofLinks();

    const Formula *getFormulaPtr() const;
    void setFormulaPtr(const Formula * const value);

    QVector<const Proof *> getLinks() const;
    void setLinks(const QVector<const Proof *> &value);

private:
    const Formula *formulaPtr; //Maybe this should just be an ordinary pointer after all... I mean, the great question is... Should this own the object? Considering it won't change anyways and if it does a new proof link oughta be created...
    QVector<const Proof *> links;
};


#endif // PROOFLINKS_H
