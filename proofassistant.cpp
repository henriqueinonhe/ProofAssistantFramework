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

    //NOTE The process is not finished yet!
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

    LineOfProof &premiseLineOfProof = *currentProof->linesOfProof.last();
    Formula *formulaPtr = premiseLineOfProof.formula.get();
    premiseProofLinks.setFormulaPtr(formulaPtr);
    currentProof->premisesLinks.push_back(premiseProofLinks);
}

void ProofAssistant::addPremise(const QString &premise)
{
    const Formula parsedPremise = currentTheory->getParser()->parse(premise);
    createPremiseLineOfProof(parsedPremise);
    linkPremise(premise); //NOTE Maybe linking should be done only when proof is finished!
                          //So I need a temporary place to store them (both premises and conclusion)!
}

void ProofAssistant::applyInferenceRule(const QString &callCommand, const QStringList &argumentList) const
{
    const LogicalSystem &logicalSystem = *currentTheory->getParentLogic();
    InferenceRule *rule = queryInferenceProcedure<InferenceRule>(logicalSystem.getInferenceRules(), callCommand);

    if(rule == nullptr)
    {
        throw std::invalid_argument("There is no inference rule associated with this call command!");
    }

    currentProof->linesOfProof.push_back(shared_ptr<LineOfProof>(new LineOfProof(rule->apply(*currentProof, argumentList))));


    //NOTE Refactor this! Extract function!
    if(currentProof->isFinished())
    {
        currentTheory->proofs.push_back(*currentProof);

        delete currentProof;
    }
}

void ProofAssistant::applyInferenceTactic(const QString &callCommand, const QStringList &argumentList) const
{
    InferenceTactic *tactic = queryInferenceProcedure<InferenceTactic>(currentTheory->getInferenceTactics(), callCommand);

    if(tactic == nullptr)
    {
        throw std::invalid_argument("There is no inference tactic associated with this call command!");
    }

    tactic->apply(this, argumentList);
}

void ProofAssistant::setLineOfProofComment(const unsigned int lineNumber, const QString &comment) const
{
    currentProof->linesOfProof[lineNumber]->setComment(comment);
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

























