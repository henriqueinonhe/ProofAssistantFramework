#include "theory.h"
#include "logicalsystem.h"
#include "storagemanager.h"
#include <QDataStream>
#include "containerauxiliarytools.h"

Theory::Theory(const LogicalSystem * const parentLogic) :
    parentLogic(parentLogic)
{
}

QVector<shared_ptr<StringProcessor> > &Theory::getPostProcessors()
{
    return postProcessors;
}

QVector<shared_ptr<StringProcessor>> &Theory::getPreProcessors()
{
    return preProcessors;
}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, Signature *signature, const QLinkedList<Formula> &axioms) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    signature(signature),
    axioms(axioms)
{
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));
}

Theory::Theory(const LogicalSystem *parentLogic, shared_ptr<Signature> signature, QDataStream &stream) :
    parentLogic(parentLogic),
    signature(signature)
{
    stream >> *this;
}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

Signature *Theory::getSignature()
{
    return signature.get();
}

QVector<const Proof *> Theory::findProofsWithConclusion(const QString &formula) const
{
//    QVector<const Proof *> proofList;

//    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
//    {
//        if(proof->getConclusion()->formattedString() == formula)
//        {
//            proofList.push_back(proof.get());
//        }
//    });

//    return proofList;
    //FIXME
}

QVector<const Proof *> Theory::findProofsWithPremise(const QString &formula) const
{
//    QVector<const Proof *> proofList;

//    std::for_each(proofs.begin(), proofs.end(), [&formula, &proofList](const shared_ptr<Proof> &proof)
//    {
//        const QVector<const Formula *> premises = proof->getPremises();
//        bool containsPremise = std::any_of(premises.begin(), premises.end(), [&formula](const Formula * const premise)
//        {
//            return premise->formattedString() == formula;
//        });

//        if(containsPremise)
//        {
//            proofList.push_back(proof.get());
//        }
//    });

//    return proofList;
    //FIXME
}

QString Theory::getName() const
{
    return name;
}

QString Theory::getDescription() const
{
    return description;
}

QDataStream &operator <<(QDataStream &stream, const Theory &theory)
{
    stream << theory.name
           << theory.description
           << theory.signature
           << theory.axioms
           << theory.preProcessors
           << theory.postProcessors
           << theory.preFormatter
           << theory.postFormatter;

    return stream;
}

QDataStream &operator >>(QDataStream &stream, Theory &theory)
{
    stream >> theory.name
           >> theory.description
           >> theory.signature;
    theory.axioms = Formula::unserializeList(stream, theory.signature.get());
    stream >> theory.preProcessors
           >> theory.postProcessors
           >> theory.preFormatter
           >> theory.postFormatter;

    return stream;
}

QLinkedList<Formula> Theory::getAxioms() const
{
    return axioms;
}

QVector<shared_ptr<const InferenceTactic>> &Theory::getInferenceTactics()
{
    return inferenceTactics;
}

QDataStream &operator <<(QDataStream &stream, const shared_ptr<Signature> &signature)
{
    stream << *signature;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, shared_ptr<Signature> &signature)
{
    stream >> *signature;
    return stream;
}

QDataStream &operator <<(QDataStream &stream, const shared_ptr<StringProcessor> &processor)
{
    stream << *processor;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, shared_ptr<StringProcessor> &processor)
{
    stream >> *processor;
    return stream;
}
