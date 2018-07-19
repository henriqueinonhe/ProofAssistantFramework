#include "proof.h"

Proof::Proof() :
    linkedWithAxioms(true) //Empty premises are valid formulas and thus linked with axioms!
{

}

QVector<ProofLinks> Proof::getPremisesLinks() const
{
    return premisesLinks;
}

ProofLinks Proof::getConclusionLinks() const
{
    return conclusionLinks;
}

bool Proof::isFinished() const
{
    if(linesOfProof.isEmpty())
    {
        return false;
    }
    else
    {
        const Formula &conclusionFormula = *conclusionLinks.getFormulaPtr();
        const Formula lastLineOfProofFormula = linesOfProof.last()->getFormula();

        return conclusionFormula == lastLineOfProofFormula;
    }
}

QString Proof::getName() const
{
    return name;
}

void Proof::setName(const QString &value)
{
    name = value;
}

QVector<const Formula *> Proof::getPremises() const
{
    QVector<const Formula *> premises;

    std::for_each(premisesLinks.begin(), premisesLinks.end(), [&premises](const ProofLinks &links)
    {
        premises.push_back(links.getFormulaPtr());
    });

    return premises;
}

const Formula *Proof::getConclusion() const
{
    return conclusionLinks.getFormulaPtr();
}

