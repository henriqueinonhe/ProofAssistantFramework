#include "prooflinks.h"

ProofLinks::ProofLinks()
{

}

const Formula *ProofLinks::getFormulaPtr() const
{
    return formulaPtr;
}

void ProofLinks::setFormulaPtr(const Formula * const value)
{
    formulaPtr = value;
}

QVector<const Proof *> ProofLinks::getLinks() const
{
    return links;
}

void ProofLinks::setLinks(const QVector<const Proof *> &value)
{
    links = value;
}
