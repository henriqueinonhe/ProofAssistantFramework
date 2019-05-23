#include "proof.h"
#include <QDataStream>
#include "formula.h"


Proof::Proof(QDataStream &stream, const Signature * const signature) :
    premises(Formula::unserializeVector(stream, signature)),
    conclusion(stream, signature),
    linesOfProof(LineOfProof::unserializeVector(stream, signature))
{
    stream >> id
           >> name
           >> description
           >> sectioning
           >> linkedWithAxioms;
}

Proof::Proof(const uint id, const QString &name, const QString &description, const QVector<Formula> &premises, const Formula &conclusion) :
    id(id),
    name(name),
    description(description),
    premises(premises),
    conclusion(conclusion),
    linkedWithAxioms(false)
{
    insertPremisesAsLinesOfProof();
}

bool Proof::isFinished() const
{
    if(linesOfProof.isEmpty())
    {
        return false;
    }
    else
    {
        const Formula lastLineOfProofFormula = linesOfProof.last().getFormula();

        return conclusion == lastLineOfProofFormula;
    }

    //NOTE Not sure if it is done
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
        linesOfProof.push_back(LineOfProof(premiss, justification, "Premiss"));
    }
}

void Proof::addLineOfProof(const LineOfProof &lineOfProof)
{
    linesOfProof.push_back(lineOfProof);
}

QVector<LineOfProof> Proof::getLinesOfProof() const
{
    return linesOfProof;
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
    stream << proof.premises
           << proof.conclusion
           << proof.linesOfProof
           << proof.id
           << proof.name
           << proof.description
           << proof.sectioning
           << proof.linkedWithAxioms;
    return stream;
}

