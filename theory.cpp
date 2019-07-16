#include "theory.h"
#include "logicalsystem.h"
#include "storagemanager.h"
#include <QDataStream>
#include "containerauxiliarytools.h"

const QVector<shared_ptr<const InferenceTactic> > &Theory::getInferenceTactics() const
{
    return inferenceTactics;
}

StringProcessorManager &Theory::getPreFormatter()
{
    return preFormatter;
}

const StringProcessorManager &Theory::getPreFormatter() const
{
    return preFormatter;
}

StringProcessorManager &Theory::getPostFormatter()
{
    return postFormatter;
}

const StringProcessorManager &Theory::getPostFormatter() const
{
    return postFormatter;
}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const shared_ptr<Signature> &signature, const QLinkedList<Formula> &axioms) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    signature(signature),
    axioms(axioms)
{
    parser.reset(new Parser(getSignature(), parentLogic->getWffType()));
}

Theory::Theory(const LogicalSystem *parentLogic, const shared_ptr<Signature> &signature, const QVector<shared_ptr<const InferenceTactic> > &inferenceTactics, const QVector<shared_ptr<StringProcessor> > &preProcessors, const QVector<shared_ptr<StringProcessor> > &postProcessors, QDataStream &stream) :
    parentLogic(parentLogic),
    signature(signature),
    parser(new Parser(getSignature(), parentLogic->getWffType())),
    inferenceTactics(inferenceTactics)
{
    //Note to self: Why didn't I initialize everything using QDataStream
    //instead of unserializing them?
    //Because I'm unable to initialize QString with QDataStream, therefore there is no other way
    //In the future I can implement a "QString factory" so I can initialize it the right way

    stream >> this->name
           >> this->description
           >> this->signature;
    axioms = Formula::deserializeList(stream, signature.get());
    preFormatter.deserialize(stream, preProcessors);
    postFormatter.deserialize(stream, postProcessors);
}

const LogicalSystem *Theory::getParentLogic() const
{
    return parentLogic;
}

Signature *Theory::getSignature() const
{
    return signature.get();
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
           << theory.preFormatter
           << theory.postFormatter;

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

QDataStream &operator <<(QDataStream &stream, const QVector<shared_ptr<StringProcessor>> &processors)
{
    ContainerAuxiliaryTools::serializeSmartPointerContainer(stream, processors);
    return stream;
}

QDataStream &operator >>(QDataStream &stream, QVector<shared_ptr<StringProcessor> > &processors)
{
    ContainerAuxiliaryTools::deserializeSmartPointerContainer(stream, processors);
    return stream;
}
