#include "prooflinks.h"

ProofLinks::ProofLinks()
{

}

const Formula *ProofLinks::getFormula() const
{
    return formula;
}

void ProofLinks::setFormula(const Formula * const value)
{
    formula = value;
}

QVector<const Proof *> ProofLinks::getLinks() const
{
    return links;
}
