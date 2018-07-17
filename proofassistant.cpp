#include "proofassistant.h"

ProofAssistant::ProofAssistant()
{

}

Theory *ProofAssistant::getCurrentTheory() const
{
    return currentTheory;
}

void ProofAssistant::setCurrentTheory(Theory *value)
{
    currentTheory = value;
}

Proof *ProofAssistant::getCurrentProof() const
{
    return currentProof;
}

void ProofAssistant::setCurrentProof(Proof *value)
{
    currentProof = value;
}

void ProofAssistant::createProof()
{
    checkCurrentTheoryIsNull();

    currentProof = new Proof;
    proofOwner = true;
}

void ProofAssistant::setProofName(const QString &name)
{
    checkCurrentProofIsNull();

    currentProof->setName(name);
}

void ProofAssistant::createPremiseLineOfProof(const Formula &parsedPremise)
{
    shared_ptr<LineOfProof> newPremiseLine = make_shared<LineOfProof>(LineOfProof(parsedPremise, Justification("Premise", QStringList())));

    currentProof->linesOfProof.push_back(newPremiseLine);
}

void ProofAssistant::linkPremise(const QString &premise)
{
    ProofLinks premiseProofLinks;

    premiseProofLinks.setLinks(currentTheory->findProofsWithConclusion(premise));

    currentProof->linesOfProof.last()->getFormula(); //Ok There is a problem here....
    premiseProofLinks.setFormula();
//    currentProof->getPremisesLinks().push_back(premiseProofLinks);
}

void ProofAssistant::addPremise(const QString &premise)
{
    const Formula parsedPremise = currentTheory->getParser()->parse(premise);
    createPremiseLineOfProof(parsedPremise);
    linkPremise(premise);
}

void ProofAssistant::checkCurrentTheoryIsNull() const
{
    if(currentTheory == nullptr)
    {
        throw std::runtime_error("Current theory pointer is null!");
    }
}

void ProofAssistant::checkCurrentProofIsNull() const
{
    if(currentProof == nullptr)
    {
        throw std::runtime_error("Current proof pointer is null!");
    }
}
