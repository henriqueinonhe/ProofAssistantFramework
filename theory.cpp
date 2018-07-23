#include "theory.h"
#include "logicalsystem.h"

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{

}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const QLinkedList<Formula> axioms, const QStringList &inferenceTacticsPluginsNameList, const QStringList &preProcessorPluginsNameList, const QStringList &postProcessorPluginsNameList) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    axioms(axioms),
    inferenceTacticsPluginsNameList(inferenceTacticsPluginsNameList),
    preProcessorPluginsNameList(preProcessorPluginsNameList),
    postProcessorPluginsNameList(postProcessorPluginsNameList)
{
    //Gotta do some validation! Axioms for instance, there cannot be duplicates!


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

QString Theory::getName() const
{
    return name;
}

void Theory::setName(const QString &value)
{
    name = value;
}

QString Theory::getDescription() const
{
    return description;
}

void Theory::setDescription(const QString &value)
{
    description = value;
}

QDataStream &operator <<(QDataStream &stream, const Theory &theory)
{
    //This probably will have severeal adjustments in the future!
    stream << theory.name << theory.description << theory.axioms << theory.inferenceTacticsPluginsNameList << theory.preProcessorPluginsNameList << theory.postProcessorPluginsNameList;

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Theory &theory)
{

    stream >> theory.name >> theory.description;
    theory.axioms = Formula::unserializeList(stream, theory.signature.get());
    stream >> theory.inferenceTacticsPluginsNameList >> theory.preProcessorPluginsNameList >> theory.postProcessorPluginsNameList;

    return stream;
}

QLinkedList<Formula> Theory::getAxioms() const
{
    return axioms;
}



