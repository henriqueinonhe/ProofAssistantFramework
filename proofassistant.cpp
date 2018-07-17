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

void ProofAssistant::addPremiss(const QString &premiss)
{
    Formula parsedPremiss = currentTheory->getParser()->parse(premiss);


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
