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

QVector<Formula> Proof::getPremises() const
{
    QVector<Formula> premises;

    std::for_each(premisesLinks.begin(), premisesLinks.end(), [&premises](const ProofLinks &links)
    {
        premises.push_back(links.getFormula());
    });

    return premises;
}

Formula Proof::getConclusion() const
{
    return conclusionLinks.getFormula();
}


QDataStream &operator <<(QDataStream &stream, const Proof &proof)
{
    stream << proof.id << proof.name << proof.description << proof.premisesLinks << proof.conclusionLinks << proof.linesOfProof << proof.sectioning;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, Proof &proof)
{
    stream >> proof.id >> proof.name >> proof.description >> proof.premisesLinks >> proof.conclusionLinks >> proof.linesOfProof >> proof.sectioning;
    return stream;
}
