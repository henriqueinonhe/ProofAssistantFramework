#ifndef PROOF_H
#define PROOF_H

#include "lineofproof.h"
#include "lineofproofsectionmanager.h"
#include "formula.h"

class Formula;
class ProofAssistant;

class Proof
{
public:
    Proof(const uint id,
          const QString &name,
          const QString &description,
          const QVector<Formula> &premises,
          const Formula &conclusion);

    bool isFinished() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QVector<Formula> getPremises() const;

    Formula getConclusion() const;

    QVector<LineOfProof> getLinesOfProof() const;
    void addLineOfProof(const LineOfProof &lineOfProof);

    bool getLinkedWithAxioms() const;

    unsigned int getId() const;

private:
    unsigned int id;
    QString name;
    QString description;
    QVector<Formula> premises;
    Formula conclusion;
    QVector<LineOfProof> linesOfProof;
    LineOfProofSectionManager sectioning;
    bool linkedWithAxioms;

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const Proof &proof);
    friend QDataStream &operator >>(QDataStream &stream, Proof &proof);
};

QDataStream &operator <<(QDataStream &stream, const Proof &proof);
QDataStream &operator >>(QDataStream &stream, Proof &proof);

#endif // PROOF_H
