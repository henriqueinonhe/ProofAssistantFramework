#include "proof.h"

Proof::Proof() :
    linkedWithAxioms(true) //Empty premises are valid formulas and thus linked with axioms!
{

}

QVector<ProofLinks> &Proof::getPremisesLinks()
{
    return premisesLinks;
}

ProofLinks &Proof::getConclusionLinks()
{
    return conclusionLinks;
}

bool Proof::isFinished() const
{
    return conclusionLinks.getFormula()->formattedString() == demonstration.last().getSentence();
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
        premises.push_back(links.getFormula());
    });

    return premises;
}

const Formula *Proof::getConclusion() const
{
    return conclusionLinks.getFormula();
}
