#include "proofassistant.h"
#include <memory>
#include "proof.h"
#include "logicalsystem.h"
#include "theory.h"
#include "inferencetactic.h"


ProofAssistant::ProofAssistant(const Theory * const theory, const shared_ptr<Proof> &proof) :
    theory(theory),
    proof(proof)
{
}

void ProofAssistant::applyInferenceRule(const QString &callCommand, const QStringList &argumentList)
{
    const auto &logicalSystem = *theory->getParentLogic();
    const auto *rule = queryInferenceProcedure(logicalSystem.getInferenceRules(), callCommand);

    if(rule == nullptr)
    {
        throw std::invalid_argument("There is no inference rule associated with this call command!");
    }

    proof->addLineOfProof(rule->apply(*theory->parser, *proof, argumentList));
}

void ProofAssistant::applyInferenceTactic(const QString &callCommand, const QStringList &argumentList) const
{
    const auto *tactic = queryInferenceProcedure(theory->getInferenceTactics(), callCommand);

    if(tactic == nullptr)
    {
        throw std::invalid_argument("There is no inference tactic associated with this call command!");
    }

    //tactic->apply(this, argumentList); Gotta fix inference tactics
}

void ProofAssistant::setLineOfProofComment(const unsigned int lineNumber, const QString &comment)
{
    proof->setComment(lineNumber, comment);
}

const Proof &ProofAssistant::getProof() const
{
    return *proof;
}

























