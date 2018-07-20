#include "theory.h"
#include "logicalsystem.h"

Theory::Theory()
{

}

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{

}

void Theory::addAxiom(const QString &axiom)
{
    //NOTE Maybe I should prevent duplicates...

    if(parentLogic == nullptr)
    {
        throw std::runtime_error("This theory doesn't belong to any logical system!");
    }

    if(!signature)
    {
        throw std::runtime_error("Signature is not set yet!");
    }



    axioms.push_back(parser->parse(axiom));
}

void Theory::removeAxiom(const QString &axiom)
{
    axioms.removeAll(parser->parse(axiom));
}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

void Theory::setParentLogic(const LogicalSystem * const value)
{
    parentLogic = value;
}

Signature *Theory::getSignature() const
{
    return signature.get();
}

void Theory::setSignature(Signature * const signature)
{
    if(parentLogic == nullptr)
    {
        throw std::runtime_error("This theory doesn't belong to any logical system!");
    }

    this->signature.reset(signature);
    parser.reset(new Parser(signature, parentLogic->getWffType()));
}

Parser *Theory::getParser() const
{
    return parser.get();
}

QVector<const Proof *> Theory::findProofsWithConclusion(const QString &formula) const
{
    QVector<const Proof *> proofList;

    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
    {
        if(proof->getConclusion()->formattedString() == formula)
        {
            proofList.push_back(proof.get());
        }
    });

    return proofList;
}

QVector<const Proof *> Theory::findProofsWithPremise(const QString &formula) const
{
    QVector<const Proof *> proofList;

    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
    {
        const QVector<const Formula *> premises = proof->getPremises();
        bool containsPremise = std::any_of(premises.begin(), premises.end(), [&formula](const Formula * const premise)
        {
            return premise->formattedString() == formula;
        });

        if(containsPremise)
        {
            proofList.push_back(proof.get());
        }
    });

    return proofList;
}

QVector<InferenceTactic *> Theory::getInferenceTactics() const
{
    return inferenceTactics;
}

QLinkedList<Formula> Theory::getAxioms() const
{
    return axioms;
}


