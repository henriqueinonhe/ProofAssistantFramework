#include "proof.h"
#include <QDataStream>
#include "formula.h"
#include "lineofproof.h"
#include "containerauxiliarytools.h"
#include "qtclassesdeserialization.h"

Proof::Proof(QDataStream &stream, Signature * const signature) :
    id(QtDeserialization::deserializeUInt(stream)),
    name(QtDeserialization::deserializeQString(stream)),
    description(QtDeserialization::deserializeQString(stream)),
    premises(Formula::deserializeVector(stream, signature)),
    conclusion(stream, signature),
    linesOfProof(LineOfProof::deserializeVector(stream, signature)),
    sectioning(stream),
    linkedWithAxioms(QtDeserialization::deserializeBool(stream))
{
}


Proof::Proof(const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) :
    id(id),
    name(name),
    description(description),
    premises(premises),
    conclusion(conclusion)
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

void Proof::insertPremisesAsLinesOfProof()
{
    Justification justification("Premiss", QStringList());
    for(const Formula &premiss : premises)
    {
        linesOfProof.push_back(createLineOfProof(premiss, justification));
    }
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
    //NOTE Maybe add a boundary check
    linesOfProof[lineNumber]->setComment(comment);
}

QVector<const LineOfProof *> Proof::getLinesOfProof() const
{
    QVector<const LineOfProof *> vector;
    ContainerAuxiliaryTools::adatpFromSmartPointerContainer(linesOfProof, vector);
    return vector;
}

const LineOfProof &Proof::getLineOfProof(const int lineNumber) const
{
    if(lineNumber <= 0)
    {
        throw invalid_argument("Line number must be a positive integer!");
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

