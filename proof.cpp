#include "proof.h"
#include <QDataStream>
#include "formula.h"
#include "lineofproof.h"
#include "containerauxiliarytools.h"
#include "qtclassesdeserialization.h"

Proof::Proof(QDataStream &stream, const Signature * const signature) :
    id(QtDeserialization::deserializeUInt(stream)),
    name(QtDeserialization::deserializeQString(stream)),
    description(QtDeserialization::deserializeQString(stream)),
    premises(Formula::deserializeVector(stream, signature)),
    conclusion(stream, signature),
    linesOfProof(LineOfProof::deserializeVector(stream, signature)), //FIXME This is gonnna be a problem with polymorphic line of proof
    sectioning(stream),
    linkedWithAxioms(QtDeserialization::deserializeBool(stream))
{
}

void Proof::serialize(QDataStream &stream) const
{
    stream << id
           << name
           << description
           << premises
           << conclusion
           << linesOfProof
           << sectioning
           << linkedWithAxioms;
}

bool Proof::isFinished() const
{
    if(linesOfProof.isEmpty())
    {
        return false;
    }
    else
    {
        const auto lastLineOfProofFormula = linesOfProof.last()->getFormula();
        return conclusion == lastLineOfProofFormula && isFinishedAdditionalChecks();
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
    return premises;
}

Formula Proof::getConclusion() const
{
    return conclusion;
}

bool Proof::getLinkedWithAxioms() const
{
    return linkedWithAxioms;
}

unsigned int Proof::getId() const
{
    return id;
}

Proof::Proof(const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) :
    id(id),
    name(name),
    description(description),
    premises(premises),
    conclusion(conclusion)
{
}

void Proof::insertPremisesAsLinesOfProof()
{
    Justification justification("Premiss", QStringList());
    for(const Formula &premiss : premises)
    {
        linesOfProof.push_back(createLineOfProof(premiss, justification));
    }
}

void Proof::additionalSetup()
{

}

shared_ptr<LineOfProof> Proof::createLineOfProof(const Formula &premiss, const Justification &justification) const
{
    return make_shared<LineOfProof>(premiss, justification);
}

void Proof::addLineOfProof(const shared_ptr<LineOfProof> &lineOfProof)
{
    linesOfProof.push_back(lineOfProof);
}

bool Proof::isFinishedAdditionalChecks() const
{
    //Designed to be overriden by subclasses to implement additional constraints
    //in considering a proof finished
    return true;
}

void Proof::setComment(const unsigned int lineNumber, const QString &comment)
{
    if(lineNumber >= linesOfProof.size())
    {
        throw invalid_argument("There is no line number associated with this index!");
    }

    linesOfProof[lineNumber]->setComment(comment);
}

QVector<const LineOfProof *> Proof::getLinesOfProof() const
{
    //Note: It MUST be a raw pointer vector because it is both non owning
    //and polymorphic
    return ContainerAuxiliaryTools::adaptFromSmartPointerContainer
            <QVector<shared_ptr<LineOfProof>>, QVector<const LineOfProof *>>(linesOfProof);
}

const LineOfProof &Proof::getLineOfProof(const int lineNumber) const
{
    if(lineNumber <= 0)
    {
        throw invalid_argument("Line number must be a positive integer!");
    }

    if(lineNumber > linesOfProof.size())
    {
        throw invalid_argument("There is no line number associated with this index!");
    }

    const int zeroIndexCompensation = 1;
    return *linesOfProof[lineNumber - zeroIndexCompensation];
}

QString Proof::getDescription() const
{
    return description;
}

void Proof::setDescription(const QString &value)
{
    description = value;
}


QDataStream &operator <<(QDataStream &stream, const Proof &proof)
{
    proof.serialize(stream);
    return stream;
}

