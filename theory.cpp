#include "theory.h"
#include "logicalsystem.h"
#include "storagemanager.h"
#include <QDataStream>
#include "containerauxiliarytools.h"
#include "qtclassesdeserialization.h"

const QVector<shared_ptr<const InferenceTactic> > &Theory::getInferenceTactics() const
{
    return inferenceTactics;
}

const StringProcessorManager &Theory::getPreFormatter() const
{
    return preFormatter;
}

const StringProcessorManager &Theory::getPostFormatter() const
{
    return postFormatter;
}

StringProcessorManager &Theory::getPreFormatter()
{
    return preFormatter;
}

StringProcessorManager &Theory::getPostFormatter()
{
    return postFormatter;
}

Theory::Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const shared_ptr<Signature> &signature, const QLinkedList<Formula> &axioms) :
    parentLogic(parentLogic),
    name(name),
    description(description),
    signature(signature),
    parser(signature.get(), parentLogic->getWffType()),
    axioms(axioms)
{
}

Theory::Theory(const LogicalSystem *parentLogic, const shared_ptr<Signature> &signature, const QVector<shared_ptr<const InferenceTactic> > &inferenceTactics, const QVector<shared_ptr<StringProcessor> > &preProcessors, const QVector<shared_ptr<StringProcessor> > &postProcessors, QDataStream &stream) :
    parentLogic(parentLogic),
    name(QtDeserialization::deserializeQString(stream)),
    description(QtDeserialization::deserializeQString(stream)),
    signature(signature),
    parser(stream, signature.get()),
    axioms(Formula::deserializeList(stream, signature.get())),
    inferenceTactics(inferenceTactics),
    preFormatter(stream, preProcessors),
    postFormatter(stream, postProcessors)
{
    /* Note: Signature, PreProcessors and PostProcessors should come already deserialized */
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
           << theory.parser
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
