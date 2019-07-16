#ifndef PROOF_H
#define PROOF_H

#include "lineofproof.h"
#include "lineofproofsectionmanager.h"
#include "formula.h"

class Formula;
class ProofAssistant;
class QDataStream;

class Proof
{
public:
    Proof() = default;
    Proof(QDataStream &stream, Signature * const signature);
    Proof(const uint id,
          const QString &name,
          const QString &description,
          const QVector<Formula> &premises,
          const Formula &conclusion);

    virtual void serialize(QDataStream &stream) const;
    virtual void deserialize(QDataStream &stream, Signature * const signature);

    virtual bool isFinished() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QVector<Formula> getPremises() const;

    Formula getConclusion() const;

    QVector<LineOfProof> getLinesOfProof() const;
    LineOfProof getLineOfProof(const int lineNumber) const;
    void addLineOfProof(const LineOfProof &lineOfProof);
    virtual void setComment(const unsigned int lineNumber, const QString &comment);

    bool getLinkedWithAxioms() const;

    unsigned int getId() const;

protected:
    void insertPremisesAsLinesOfProof();

    unsigned int id;
    QString name;
    QString description;
    QVector<Formula> premises;
    Formula conclusion;
    QVector<LineOfProof> linesOfProof;
    LineOfProofSectionManager sectioning;
    bool linkedWithAxioms;

    friend QDataStream &operator <<(QDataStream &stream, const Proof &proof);
};

QDataStream &operator <<(QDataStream &stream, const Proof &proof);

#endif // PROOF_H
